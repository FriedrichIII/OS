/*
 * TODO Questions
 *
 * Is it always the case that 1 fat entry is associated to 1 cluster ? (size field)
 *
 */



#define FUSE_USE_VERSION 26
#define _GNU_SOURCE

#define DATA f->fs_data

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
static unsigned long to_byte_address(int clusters, int sectors, int dir_entries);
static int find_next_cluster(int current_cluster);
static unsigned int get_fat_entry(unsigned int fat_index);
//static int increment_dir_descr(struct vfat_dir_descr *dir);

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
	size_t fs_size;
	unsigned char *fs_data;
	// byte addresses
	unsigned long fat_begin;
	unsigned long data_begin;
};

struct vfat_search_data {
	const char	*name;
	int		found;
	struct stat	*st;
};

struct vfat_dir_descr {
	// location: nth cluster in data clusters
	// this uses the real index, i.e. FAT entry index - 2

	// first cluster of dir
	int start_cluster;
	// cluster being read. -1 if reached end of last cluster.
	int current_cluster;

	// dir entry index in cluster
	int de_index;
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

	/*
	 * Memory mapping
	 */
	// get size of fs.fat file
	f->fs_size = lseek(fd, 0L, SEEK_END);
	// seek back to 0
	lseek(fd, 0, SEEK_SET);
	// map the wole file
	f->fs_data = mmap(NULL, f->fs_size, PROT_READ, MAP_PRIVATE, f->fs, 0);

	// read the number of bytes per sector (always 512)
	// Bytes Per Sector	0x0B	16 Bits
	int bytesPerSector = byte_array_to_int(DATA, 0xB, 2);
	volumeID_fields->bytes_per_sector = bytesPerSector;

	// read the number of sectors per cluster
	// Sectors Per Cluster	0x0D	8 Bits
	int sectorsPerCluster = byte_array_to_int(DATA, 0xD, 1);
	volumeID_fields->sectors_per_cluster = sectorsPerCluster;

	// read the number of reserved sectors
	// Number of Reserved Sectors	0x0E	16 Bits
	int reservedSectors = byte_array_to_int(DATA, 0xE, 2);
	volumeID_fields->reserved_sectors = reservedSectors;

	// read the number of FATs ("always 2")
	// Number of FATs	0x10	8 Bits
	int numberOfFATs = byte_array_to_int(DATA, 0x10, 1);
	volumeID_fields->fat_count = numberOfFATs;

	// read the number of sectors per FATs
	// Sectors Per FAT	0x24	32 Bits
	int numberOfSectorsPerFAT = byte_array_to_int(DATA, 0x24, 4);
	volumeID_fields->sectors_per_fat = numberOfSectorsPerFAT;

	// read the disk address of the root directory first cluster
	// Root Directory First Cluster	0x2C	32 Bits
	int rootDirFirstCluster = byte_array_to_int(DATA, 0x2C, 4);
	volumeID_fields->root_cluster = rootDirFirstCluster;

	// check the signature, which should always be 0x55AA
	// Signature	0x1FE	16 Bits
	int signature = byte_array_to_int(DATA, 0x1FE, 2);

	if (signature != 0xAA55) {
		errx(1, "Incorrect FAT32 volume ID signature\n"
				"Got 0x%4.4X, expected 0xAA55", signature);
	}

	f->fat_begin = volumeID_fields->reserved_sectors
			* volumeID_fields->bytes_per_sector;
	f->data_begin = f->fat_begin +
			volumeID_fields->fat_count
			* volumeID_fields->sectors_per_fat
			* volumeID_fields->bytes_per_sector;

//	Debug output
	printf("bytesPerSector: %u\n"
			"sectorsPerCluster: %u\n"
			"reservedSectors: %u\n"
			"numberOfFATs: %u\n"
			"numberOfSectorsPerFAT: %u\n"
			"rootDirFirstCluster: %u\n"
			"signature: %4.4X\n",
			f->volumeID_fields.bytes_per_sector,
			f->volumeID_fields.sectors_per_cluster,
			f->volumeID_fields.reserved_sectors,
			f->volumeID_fields.fat_count,
			f->volumeID_fields.sectors_per_fat,
			f->volumeID_fields.root_cluster,
			signature);

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
 * Unused since mmap() implementation.
 *
 * random read function.
 * Read byte_count bytes from position offset in file represented by fdes and stores them in buff.
 * int fdes input file descriptor of file to be read
 * char *buffer output array to store read bytes
 * int offset input position where start the read (included)
 * int byte_count input number of bytes to be read in file
 * int return output number of bytes effectively read in file.
 *
 */
static int
r_read(int fdes,unsigned char *buffer, int offset, int byte_count)
{
	int success = 0;
	success = lseek(fdes, offset, SEEK_SET);
	if (success<0)
		errx(1, "Error in lseek");
	int result = read(fdes, buffer, byte_count);
	if (result<0)
		errx(1, "Error in read");
	return result;
}

/*
 * Increments dir entry index in dir descriptor up to the next valid
 * dir entry.
 * This updates the cluster index of dir descr if needed.
 *
 * if the end of directory is reached, returns 0, returns 1 otherwise.
 *
 * TODO problems with prototype
 */

static int
increment_dir_descr(struct vfat_dir_descr *dir)
{

	int dir_entries_per_cluster =
			f->volumeID_fields.sectors_per_cluster
			*f->volumeID_fields.bytes_per_sector/32;
	// check that de_index is not outside indicated cluster
	// or dir hasn't already been read until the end
	if (dir->de_index >= dir_entries_per_cluster
			|| dir->current_cluster==-1)
		return 0;

	// deleted entry
	unsigned char entryFirstByte = 0xE5;

	// while (deleted entry)
	while (entryFirstByte == 0xE5) {
		entryFirstByte = DATA[to_byte_address(dir->current_cluster, 0, dir->de_index)];

		// check if current entry is not end of dir
		if (entryFirstByte == 0)
			return 0;
		dir->de_index += 1;

		// test if end of cluster reached
		if (dir->de_index >= dir_entries_per_cluster) {
			// lookup for next cluster in FAT
			dir->current_cluster = find_next_cluster(dir->current_cluster);
			dir->de_index = 0;
			// last cluster reached when next_cluster == -1
			if (dir->current_cluster == -1) {
				// de_index value does not matter when current_cluster == -1
				return 0;
			}
		}
	}
	return 1;
}

/*
 * computes the DATA address.
 * to_byte_address(0, 0, 0) returns the byte address of first data cluster
 */
static unsigned long
to_byte_address(int clusters, int sectors, int dir_entries)
{
	unsigned long clusterBytes = clusters * f->volumeID_fields.sectors_per_cluster * f->volumeID_fields.bytes_per_sector;
	unsigned long sectorBytes = sectors * f->volumeID_fields.bytes_per_sector;
	unsigned long dir_entryBytes = dir_entries * 32; // because of fat32
	return clusterBytes + sectorBytes + dir_entryBytes + f->data_begin;
}

/*
 * finds next cluster, looking in FAT
 * current_cluster the cluster index in DATA clusters
 * return the next cluster index and -1 if there is no one (final cluster, bad index, ...)
 */
static int
find_next_cluster(int current_cluster)
{
	// fat index = current cluster + 2
	return get_fat_entry(current_cluster + 2) - 2;
}

static int
get_fat_entry(int fat_index)
{
	// fat index ignores 4 bits of highest weight
	fat_index = 0x0FFFFFFF & fat_index;
	// values unused in cluster chain
	if (fat_index < 2 || fat_index > 0x0FFFFFEF)
		return -1;

	return byte_array_to_int(DATA, f->fat_begin + fat_index, 4);
}

 /* end of personal methods */

/*
 * Reads one entry of directory and store the stat in fillerdata
 *
 */
static int
vfat_readdir(/* XXX add your code here, */struct vfat_dir_descr *dir, fuse_fill_dir_t filler, void *fillerdata)
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

	// TODO Read the dir entry pointed in dir
	/*
	Short Filename	0x00	11 Bytes
	Attrib Byte	0x0B	8 Bits
	First Cluster High	0x14	16 Bits
	First Cluster Low	0x1A	16 Bits
	File Size	0x1C	32 Bits
	 */



	// parse and store info in st
	filler(fillerdata, "name from dir entry", &st, 0);
	// increment dir_descr pointer
	return (1);
	/* XXX add your code here */
}

/*
 * Takes a vfat_search_data, a name and a stat associated to this name.
 * If the name of search data match to name, then the content of the pointer
 * st in vaft_search_data will be replaced by the given stat.
 */
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
	/*
	 * - find directory of file
	 * - looks for all dir entry in dir
	 * - stat is filled with corresponding direntry.
	 */

	printf("vfat_fuse_getattr with path %s\n", path);
	/* XXX add your code here */
	return 0;
}

static int
vfat_fuse_readdir(const char *path, void *data,
		  fuse_fill_dir_t filler, off_t offs, struct fuse_file_info *fi)
{
	printf("vfat_fuse_readdir with path %s\n", path);

	/*
	 * Specification:
	 * path input A path to the directory we want information about
	 * buf output buffer containing information about directory => here: data
	 * filler input pointer to fuse_fill_dir_t function that is used to add entries to buffer (see below)
	 * offset input offset in directory entries
	 * fi input A struct fuse_file_info, contains detailed information why this readdir operation was invoked.
	 * return output negated error number, or 0 if everything went OK
	 */

	/*
	 * Useful info about filler param:
	 *
	 * Function to add an entry in a readdir() operation
	 *
	 * @param buf the buffer passed to the readdir() operation
	 * @param name the file name of the directory entry
	 * @param stat file attributes, can be NULL
	 * @param off offset of the next entry or zero
	 * @return 1 if buffer is full, zero otherwise
	 *
	 *
	 * typedef int (*fuse_fill_dir_t) (void *buf, const char *name,
				const struct stat *stbuf, off_t off);
	 */



	return 0;
}

static int
vfat_fuse_read(const char *path, char *buf, size_t size, off_t offs,
	       struct fuse_file_info *fi)
{
	printf("vfat_fuse_read\n");
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
