#define FUSE_USE_VERSION 26
#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/mman.h>

#include <endian.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <iconv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function prototypes
static int byte_array_to_int(unsigned char *array, int offset, int length);
static int r_read(int fdes,unsigned char *buffer, int offset, int byte_count);

struct vfat_super {
	uint8_t		res1[3];
	char		oemname[8];
	uint16_t	bytes_per_sector;
	uint8_t		sectors_per_cluster;
	uint16_t	reserved_sectors;
	uint8_t		fat_count;
	uint16_t	root_max_entries;
	uint16_t	total_sectors_small;
	uint8_t		media_info;
	uint16_t	sectors_per_fat_small;
	uint16_t	sectors_per_track;
	uint16_t	head_count;
	uint32_t	fs_offset;
	uint32_t	total_sectors;
	uint32_t	sectors_per_fat;
	uint16_t	fat_flags;
	uint16_t	version;
	uint32_t	root_cluster;
	uint16_t	fsinfo_sector;
	uint16_t	backup_sector;
	uint8_t		res2[12];
	uint8_t		drive_number;
	uint8_t		res3;
	uint8_t		ext_sig;
	uint32_t	serial;
	char		label[11];
	char		type[8];
	char		res4[420];
	uint16_t	sig;
} __attribute__ ((__packed__));

struct vfat_direntry {
	union {
		struct {
			char		name[8];
			char		ext[3];
		};
		char			nameext[11];
	};
	uint8_t		attr;
	uint8_t		res;
	uint8_t		ctime_ms;
	uint16_t	ctime_time;
	uint16_t	ctime_date;
	uint16_t	atime_date;
	uint16_t	cluster_hi;
	uint16_t	mtime_time;
	uint16_t	mtime_date;
	uint16_t	cluster_lo;
	uint32_t	size;
} __attribute__ ((__packed__));

#define VFAT_ATTR_DIR	0x10
#define VFAT_ATTR_LFN	0xf
#define VFAT_ATTR_INVAL	(0x80|0x40|0x08)

struct vfat_direntry_lfn {
	uint8_t		seq;
	uint16_t	name1[5];
	uint8_t		attr;
	uint8_t		res1;
	uint8_t		csum;
	uint16_t	name2[6];
	uint16_t	res2;
	uint16_t	name3[2];
} __attribute__ ((__packed__));

#define VFAT_LFN_SEQ_START	0x40
#define VFAT_LFN_SEQ_DELETED	0x80
#define VFAT_LFN_SEQ_MASK	0x3f

struct vfat {
	const char	*dev;
	int		fs; // file descriptor to the filesystem file
	struct vfat_super volumeID_fields;
};

struct vfat_search_data {
	const char	*name;
	int		found;
	struct stat	*st;
};

struct vfat vfat_info, *f = &vfat_info;
iconv_t iconv_utf16;

uid_t mount_uid;
gid_t mount_gid;
time_t mount_time;
size_t pagesize;

/*
 * The dev parameter is the filename of the .fat file, the filesystem
 * to mount
 */
static void
vfat_init(const char *dev)
{
	iconv_utf16 = iconv_open("utf-8", "utf-16");
	mount_uid = getuid();
	mount_gid = getgid();
	mount_time = time(NULL);
/*
 * f->fs is the FileDescriptor of the file
 * in which we have to read all the fat
 * informations
 */
	f->fs = open(dev, O_RDONLY);
	if (f->fs < 0)
		err(1, "open(%s)", dev);

	/* Initialization of the vfat_super structure containing
	 * the volume ID info fields. The volume ID is the first cluster
	 * of the FAT32 filesystem.
	 * In the testfs.fat used, there is no MBR so the file starts
	 * with VolumeID ad byte 0
	 */
	int fd = f->fs;
	struct vfat_super* volumeID_fields = &f->volumeID_fields;
	unsigned char buffer[0x200]; // a buffer to use with the read() system call 512 bytes to read all VolumeID at once

    // reads VolumeID
	r_read(fd, buffer, 0, 0x200);

/*
//	Debug output
	int i;
	int j;
	for (i=0; i<0x20; i++) {
		printf("0x%x :", i*0x10);
		for (j=0; j<0x10; j++) {
			printf( "%02.2X ", buffer[i*0x10+j]);
		}
		printf("\n");
	}
 */

	// read the number of bytes per sector (always 512)
	// Bytes Per Sector	0x0B	16 Bits
	int bytesPerSector = byte_array_to_int(buffer, 0xB, 2);
	volumeID_fields->bytes_per_sector = bytesPerSector;

	// read the number of sectors per cluster
	// Sectors Per Cluster	0x0D	8 Bits
	int sectorsPerCluster = byte_array_to_int(buffer, 0xD, 1);
	volumeID_fields->sectors_per_cluster = sectorsPerCluster;

	// read the number of reserved sectors
	// Number of Reserved Sectors	0x0E	16 Bits
	int reservedSectors = byte_array_to_int(buffer, 0xE, 2);
	volumeID_fields->reserved_sectors = reservedSectors;

	// read the number of FATs ("always 2")
	// Number of FATs	0x10	8 Bits
	int numberOfFATs = byte_array_to_int(buffer, 0x10, 1);
	volumeID_fields->fat_count = numberOfFATs;

	// read the number of sectors per FATs
	// Sectors Per FAT	0x24	32 Bits
	int numberOfSectorsPerFAT = byte_array_to_int(buffer, 0x24, 4);
	volumeID_fields->sectors_per_fat = numberOfSectorsPerFAT;

	// read the disk address of the root directory first cluster
	// Root Directory First Cluster	0x2C	32 Bits
	int rootDirFirstCluster = byte_array_to_int(buffer, 0x2C, 4);
	volumeID_fields->root_cluster = rootDirFirstCluster;

	// check the signature, which should always be 0x55AA
	// Signature	0x1FE	16 Bits
	int signature = byte_array_to_int(buffer, 0x1FE, 2);

	if (signature != 0xAA55) {
		errx(1, "Incorrect FAT32 volume ID signature\n"
				"Got 0x%04.4X, expected 0xAA55", signature);
	}

/*
//	Debug output
	printf("bytesPerSector: %u\n"
			"sectorsPerCluster: %u\n"
			"reservedSectors: %u\n"
			"numberOfFATs: %u\n"
			"numberOfSectorsPerFAT: %u\n"
			"rootDirFirstCluster: %u\n"
			"signature: %04.4X\n",
			f->volumeID_fields.bytes_per_sector,
			f->volumeID_fields.sectors_per_cluster,
			f->volumeID_fields.reserved_sectors,
			f->volumeID_fields.fat_count,
			f->volumeID_fields.sectors_per_fat,
			f->volumeID_fields.root_cluster,
			signature);
*/
}

/* XXX add your code here */
/*
 *
 */

/*
 * Converts an array of bytes to an int.
 * Interpret array as little endian. That is byte of smalles index
 * is less significative.
 * offset : the first byte of the array from which to read
 * length : the number of bytes to read from the array
 */
static int
byte_array_to_int(unsigned char *array, int offset, int length)
{
	int result = 0;
	int i;
	for (i = 0; i < length; i++) {
		// reads the byte at ith pos from offset
		int byte = array[i+offset];

		// the ith byte is shifted to the right of i bytes
		result += byte << (i*8);
	}
	return result;
}
/*
 * random read function.
 * Read byte_count bytes from position offset in file represented by fdes and stores them in buff.
 * int fdes input file descriptor of file to be read
 * char *buffer output array to store read bytes
 * int offset input position where start the read (included)
 * int byte_count input number of bytes to be read in file
 * int return output number of bytes effectively read in file.
 */
static int r_read(int fdes,unsigned char *buffer, int offset, int byte_count) {
	int success = 0;
	success = lseek(fdes, offset, SEEK_SET);
	if (success<0)
		errx(1, "Error in lseek");
	int result = read(fdes, buffer, byte_count);
	if (result<0)
		errx(1, "Error in read");
	return result;
}

static int
vfat_readdir(/* XXX add your code here, */fuse_fill_dir_t filler, void *fillerdata)
{
	/* this stat structure is used to store the properties of a file or directory
	 * being read. It has to be passed as an argument to the filler function.
	 */
	struct stat st;
	void *buf = NULL; // we do not have to use this buf variable (according to the forum)
	struct vfat_direntry *e;
	char *name;

	memset(&st, 0, sizeof(st));
	st.st_uid = mount_uid;
	st.st_gid = mount_gid;
	st.st_nlink = 1;
	return (1);
	/* XXX add your code here */
}

static int
vfat_search_entry(void *data, const char *name, const struct stat *st, off_t offs)
{
	struct vfat_search_data *sd = data;

	if (strcmp(sd->name, name) != 0)
		return (0);

	sd->found = 1;
	*sd->st = *st;

	return (1);
}

/*
 * The return value of vfat_resolve tells whether the searched path exists in
 * the filesystem or not.
 */
static int
vfat_resolve(const char *path, struct stat *st)
{
	struct vfat_search_data sd;
	return (1);
	/* XXX add your code here */
}

static int
vfat_fuse_getattr(const char *path, struct stat *st)
{
	printf("vfat_fuse_getattr\n");
	/* XXX add your code here */
	return 0;
}

static int
vfat_fuse_readdir(const char *path, void *data,
		  fuse_fill_dir_t filler, off_t offs, struct fuse_file_info *fi)
{
	printf("vfat_fuse_readdir\n");



	return 0;
}

static int
vfat_fuse_read(const char *path, char *buf, size_t size, off_t offs,
	       struct fuse_file_info *fi)
{
	printf("vfat_fuse_readdir\n");
	/* XXX add your code here */
	return 0;
}

static int
vfat_opt_args(void *data, const char *arg, int key, struct fuse_args *oargs)
{
	if (key == FUSE_OPT_KEY_NONOPT && !f->dev) {
		f->dev = strdup(arg);
		return (0);
	}
	return (1);
}

static struct fuse_operations vfat_ops = {
	.getattr = vfat_fuse_getattr,
	.readdir = vfat_fuse_readdir,
	.read = vfat_fuse_read,
};

int
main(int argc, char **argv)
{
	struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

	fuse_opt_parse(&args, NULL, NULL, vfat_opt_args);

	if (!f->dev)
		errx(1, "missing file system parameter");

	vfat_init(f->dev);
	return (fuse_main(args.argc, args.argv, &vfat_ops, NULL));
}
