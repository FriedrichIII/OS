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
static int byte_array_to_int(char *array, int offset, int length);

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
	 */
	int fd = f->fs;
	struct vfat_super* volumeID_fields = &f->volumeID_fields;
	char buffer[4]; // a buffer to use with the read() system call

	volumeID_fields->bytes_per_sector = 512; // always 512

	// read the number of sectors per cluster
	lseek(fd, 0xD, SEEK_SET);
	read(fd, buffer, 1);
	int sectorsPerCluster = byte_array_to_int(buffer, 0, 4);
	volumeID_fields->sectors_per_cluster = sectorsPerCluster;

	// read the number of reserved sectors
	lseek(fd, 0xE, SEEK_SET);
	read(fd, buffer, 2);
	int reservedSectors = byte_array_to_int(buffer, 0, 4);
	volumeID_fields->reserved_sectors = reservedSectors;

	// read the number of FATs ("always 2")
	lseek(fd, 0x10, SEEK_SET);
	read(fd, buffer, 1);
	int numberOfFATs = byte_array_to_int(buffer, 0, 4);
	volumeID_fields->fat_count = numberOfFATs;

	// read the number of sectors per FATs
	lseek(fd, 0x24, SEEK_SET);
	read(fd, buffer, 4);
	int numberOfSectorsPerFAT = byte_array_to_int(buffer, 0, 4);
	volumeID_fields->sectors_per_fat = numberOfSectorsPerFAT;

	// read the disk address of the root directory first cluster
	lseek(fd, 0x2C, SEEK_SET);
	read(fd, buffer, 4);
	int rootDirFirstCluster = byte_array_to_int(buffer, 0, 4);
	volumeID_fields->root_cluster = rootDirFirstCluster;

	// check the signature, which should always be 0xAA55
	lseek(fd, 0x1FE, SEEK_SET);
	read(fd, buffer, 2);
	int signature = byte_array_to_int(buffer, 0, 4);
	if (signature != 0xAA55) {
		errx(1, "Incorrect FAT32 volume ID signature");
	}
}

/* XXX add your code here */
/*
 *
 */

/*
 * Converts an array of bytes to an int
 * offset : the first byte of the array from which to read
 * length : the number of bytes to read from the array
 */
static int
byte_array_to_int(char *array, int offset, int length)
{
	int result = 0;
	int i;
	for (i = offset; i < length; i++) {
		result = result << 8;
		result += array[i];
	}
	return result;
}

static int
vfat_readdir(/* XXX add your code here, */fuse_fill_dir_t filler, void *fillerdata)
{
	struct stat st;
	void *buf = NULL;
	struct vfat_direntry *e;
	char *name;

	memset(&st, 0, sizeof(st));
	st.st_uid = mount_uid;
	st.st_gid = mount_gid;
	st.st_nlink = 1;

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

static int
vfat_resolve(const char *path, struct stat *st)
{
	struct vfat_search_data sd;

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
	/* XXX add your code here */
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
