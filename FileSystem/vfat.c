/*
 * TODO Questions
 *
 * Is it always the case that 1 fat entry is associated to 1 cluster ? (size field)
 *
 * fuse_fill_dir_t Takes a name as parameter: short name or long name?
 *
 * is the conversion uint8_t <- int working just as "take least significant bits?"
 * => yes and no sign subtilities!
 *
 * how has to be set time in st.st_?tim (which format)
 */



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
#include <time.h>



/* macros */
#define DATA f->fs_data
#define GET_ENTRY_FIELD(DIR, OFFSET, LENGTH) byte_array_to_int(DATA, to_byte_address(DIR->current_cluster, 0, DIR->de_index)+OFFSET, LENGTH)
// direntries offsets
#define SFN_OFFSET 0x0
#define SFN_LENGTH 11
#define ATTRIB_OFFSET 0xB
#define ATTRIB_LENGTH 1
#define RES_OFFSET 0xC
#define RES_LENGTH 1
#define CTMS_OFFSET 0xD
#define CTMS_LENGTH 1
#define CTT_OFFSET 0xE
#define CTT_LENGTH 2
#define CTD_OFFSET 0x10
#define CTD_LENGTH 2
#define ATD_OFFSET 0x12
#define ATD_LENGTH 2
#define CLUSHI_OFFSET 0x14
#define CLUSHI_LENGTH 2
#define MTT_OFFSET 0x16
#define MTT_LENGTH 2
#define MTD_OFFSET 0x18
#define MTD_LENGTH 2
#define CLUSLO_OFFSET 0x1A
#define CLUSLO_LENGTH 2
#define SIZE_OFFSET 0x1C
#define SIZE_LENGTH 4

// time mask
#define SEC_MASK 0x001F
#define SEC_SHFT 0
#define MIN_MASK 0x07E0
#define MIN_SHFT 5
#define HOU_MASK 0xF800
#define HOU_SHFT 11
#define DAY_MASK 0x001F
#define DAY_SHFT 0
#define MON_MASK 0x01E0
#define MON_SHFT 5
#define YEA_MASK 0xFE00
#define YEA_SHFT 7

// lfn_direntries offset
#define SEQ_OFFSET 0x0
#define NAM1_OFFSET 0x1
#define NAM1_SIZE 5
#define RES1_OFFSET 0xC
#define CSM_OFFSET 0xD
#define NAM2_OFFSET 0xE
#define NAM2_SIZE 6
#define RES2_OFFSET 0x1A
#define NAM3_OFFSET 0x1C
#define NAM3_SIZE 2
// one byte
#define BYTE 1
// 2 bytes
#define WORD 2


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


// Function prototypes

//static int r_read(int fdes,unsigned char *buffer, int offset, int byte_count); // Unused
static unsigned int byte_array_to_int(unsigned char *array, int offset, int length);
static unsigned long to_byte_address(int clusters, int sectors, int dir_entries);
static int find_next_cluster(int current_cluster);
static unsigned int get_fat_entry(unsigned int fat_index);
static int increment_dir_descr(struct vfat_dir_descr *dir);
static char *read_lfn(struct vfat_dir_descr *dir);
static void read_dir_entry(struct vfat_dir_descr *dir, struct vfat_direntry *direntry);
static void interpret_sfn(const char *name, const char *ext, char *buf);
static void reset_dir_descr(struct vfat_dir_descr *dir);
static struct timespec *make_timespec(struct timespec *buff, int date, int time, int ms);
static void read_dir_entry_lfn(struct vfat_dir_descr *dir, struct vfat_direntry_lfn *direntry_lfn);
void LFNEntriesToFileName(struct vfat_direntry_lfn LFNEntries[], size_t numberOfEntries, char* fileName);
void uint16ToChars(uint16_t value, char* bytes);

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

/* Personnal code section */

/*
 * Converts an array of bytes to an int.
 * Interpret array as little endian. That is byte of smalles index
 * is less significative.
 * offset : the first byte of the array from which to read
 * length : the number of bytes to read from the array
 */
static unsigned int
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
 */

/*
 * Increments dir entry index in dir descriptor up to the next valid
 * dir entry.
 * This updates the cluster index of dir descr if needed.
 *
 * if the end of directory is reached, returns 0, returns 1 otherwise.
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
		} // switched to next cluster
	} // end while
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

static unsigned int
get_fat_entry(unsigned int fat_index)
{
	// fat index ignores 4 bits of highest weight
	fat_index = 0x0FFFFFFF & fat_index;
	// values unused in cluster chain
	if (fat_index < 2 || fat_index > 0x0FFFFFEF)
		return -1;

	return byte_array_to_int(DATA, f->fat_begin + fat_index, 4);
}

/*
 * reads and interprets long file names
 * dir the dir descr that indicates which dir entry to read
 * return the long name in utf8 format
 * see http://man7.org/linux/man-pages/man3/iconv.3.html
 *
 * TODO implement read_lfn
 */
static char*
read_lfn(struct vfat_dir_descr *dir, char* fileName)
{
	char attrib_byte;
	/*
	 * The max. filename length when LFN is used is
	 * 255 UTF-16 characters. A code unit in UTF-16 is
	 * 16 bits. Every char is represented with
	 * one code unit (most of the time), or two (32 bits).
	 * However here it can never be two.
	 * Therefore the max. filename length cannot exceed
	 * 255 * 2 bytes = 510 bytes.
	 * (1021 for the '\0' ending character)
	 */
	struct vfat_direntry_lfn LFNEntries[20];
	unsigned short i = 0;
	// char longFileName[511];
	do {
		read_dir_entry_lfn(dir, &LFNEntries[i]);
		if(increment_dir_descr(dir) == 0) {
			/* Returns 0 if the end of the directory has been reached.
			 * It should not happen in this loop.
			 */
			return fileName;
		}
		attrib_byte = GET_ENTRY_FIELD(dir, ATTRIB_OFFSET, dir->de_index);
	} while((attrib_byte & VFAT_ATTR_LFN) == VFAT_ATTR_LFN);


	LFNEntriesToFileName(LFNEntries, i + 1, fileName);
	return fileName;
}

void LFNEntriesToFileName(struct vfat_direntry_lfn LFNEntries[], size_t numberOfEntries, char* fileName) {
	char bytes[2];
	unsigned short i;
	for (i = numberOfEntries - 1 ; i >= 0; --i) {
		strcpy(fileName, uint16ToChars(LFNEntries[i].name1, bytes));
		strcpy(fileName, uint16ToChars(LFNEntries[i].name2, bytes));
		strcpy(fileName, uint16ToChars(LFNEntries[i].name3, bytes));
	}
	strcpy(fileName, "\0");
}

void uint16ToChars(uint16_t value, char* bytes) {
	char low = value & 0xFF;
	char high = value >> 8;
	bytes[0] = high;
	bytes[1] = low;
}

static void
read_dir_entry(struct vfat_dir_descr *dir, struct vfat_direntry *direntry)
{
	int i;
	// copies sfn into direntry nameext
	for (i=0; i<11; i++) {
		direntry->nameext[i] = GET_ENTRY_FIELD(dir, SFN_OFFSET, SFN_LENGTH);
	}
	// fills all other fields
	direntry->attr = GET_ENTRY_FIELD(dir, ATTRIB_OFFSET, ATTRIB_LENGTH);
	direntry->res = GET_ENTRY_FIELD(dir, RES_OFFSET, RES_LENGTH);
	direntry->ctime_ms = GET_ENTRY_FIELD(dir, CTMS_OFFSET, CTMS_LENGTH);
	direntry->ctime_time = GET_ENTRY_FIELD(dir, CTT_OFFSET, CTT_LENGTH);
	direntry->ctime_date = GET_ENTRY_FIELD(dir, CTD_OFFSET, CTD_LENGTH);
	direntry->atime_date = GET_ENTRY_FIELD(dir, ATD_OFFSET, ATD_LENGTH);
	direntry->cluster_hi = GET_ENTRY_FIELD(dir, CLUSHI_OFFSET, CLUSHI_LENGTH);
	direntry->mtime_time = GET_ENTRY_FIELD(dir, MTT_OFFSET, MTT_LENGTH);
	direntry->mtime_date = GET_ENTRY_FIELD(dir, MTD_OFFSET, MTD_LENGTH);
	direntry->cluster_lo = GET_ENTRY_FIELD(dir, CLUSLO_OFFSET, CLUSLO_LENGTH);
	direntry->size = GET_ENTRY_FIELD(dir, SIZE_OFFSET, SIZE_LENGTH);
}

/*
 * translates nameext into correct name.ext form
 * filling spaces are removed.
 */
static void
interpret_sfn(const char *name, const char *ext, char *buf)
{
	// skips spaces at the end
	int name_end = 7;
	while((name_end >= 0) && (name[name_end]==' ')) name_end--;

	int ext_end = 2;
	while((ext_end >= 0) && (ext[ext_end]==' ')) ext_end--;

	if (name_end == -1 && ext_end == -1) {
		buf[0] = '\0';
		return;
	}
	int i;
	// indexes [0; 0]
	// if first
	buf[0] = name[0] == 0x0E? 0x5E : name[0];

	// indexes [1; name_end]
	for (i=1; i<=name_end; i++) {
		buf[i] = name[i];
	}

	// indexes [name_end+1; name_end+1]
	buf[name_end+1] = '.';

	// indexes [name_end+2; name_end+2+ext_end]
	for (i=0; i<=ext_end; i++) {
		buf[name_end+2+i] = ext[i];
	}

	// indexes [name_end+2+ext_end+1; name_end+2+ext_end+1]
	buf[name_end+ext_end+3] = '\0';
}

// set dir to point on it's first entry, according to start_cluster field
static void
reset_dir_descr(struct vfat_dir_descr *dir)
{
	dir->current_cluster = dir->start_cluster;
	dir->de_index = 0;
}


static struct timespec *
make_timespec(struct timespec *buff, int date, int time, int ms)
{
	struct tm tm_time;
	memset(&tm_time, 0, sizeof(tm_time));
	tm_time.tm_sec = ((time&SEC_MASK)>>SEC_SHFT) * 2 + ms/100;
	tm_time.tm_min = ((time&MIN_MASK)>>MIN_SHFT);
	tm_time.tm_hour = ((time&HOU_MASK)>>HOU_SHFT);
	tm_time.tm_mday = ((date&DAY_MASK)>>DAY_SHFT);
	tm_time.tm_mon = ((date&MON_MASK)>>MON_SHFT)-1;
	tm_time.tm_year = ((date&YEA_MASK)>>YEA_SHFT) + 1980 - 1900;

	buff->tv_sec = mktime(&tm_time);
	buff->tv_nsec = (ms%100)*10*1000*1000;
	return buff;
}


static void
read_dir_entry_lfn(struct vfat_dir_descr *dir, struct vfat_direntry_lfn *direntry_lfn)
{
	int i;
	direntry_lfn->seq = GET_ENTRY_FIELD(dir, SEQ_OFFSET, BYTE);
	for (i=0; i<NAM1_SIZE; i++) {
		direntry_lfn->name1[i] = GET_ENTRY_FIELD(dir, NAM1_OFFSET+i*WORD, WORD);
	}
	direntry_lfn->attr = GET_ENTRY_FIELD(dir, ATTRIB_OFFSET, BYTE);
	direntry_lfn->res1 = GET_ENTRY_FIELD(dir, RES1_OFFSET, BYTE);
	direntry_lfn->csum = GET_ENTRY_FIELD(dir, CSM_OFFSET, BYTE);
	for(i=0; i<NAM2_SIZE; i++) {
		direntry_lfn->name2[i] = GET_ENTRY_FIELD(dir, NAM2_OFFSET+i*WORD, WORD);
	}
	direntry_lfn->res2 = GET_ENTRY_FIELD(dir, RES2_OFFSET, WORD);
	for (i=0; i<NAM3_SIZE; i++) {
		direntry_lfn->name3[i] = GET_ENTRY_FIELD(dir, NAM3_OFFSET+i*WORD, WORD);
	}
}
 /* end of personal methods */

/*
 * Reads one entry of directory and store the stat in fillerdata
 * Returns 0 when fillerdata is full or when end of dir is reached
 *
 * TODO check vfat_readdir
 */
static int
vfat_readdir(struct vfat_dir_descr *dir, fuse_fill_dir_t filler, void *fillerdata)
{
	printf("reading dir...\n");
	if (dir->current_cluster == -1)
		return 0;

	/* this stat structure is used to store the properties of a file or directory
	 * being read. It has to be passed as an argument to the filler function.
	 */
//	void *buf = NULL; // we do not have to use this buf variable (according to the forum)
	struct vfat_direntry e;
	char *name = NULL;
	uint8_t attrib_byte = GET_ENTRY_FIELD(dir, ATTRIB_OFFSET, ATTRIB_LENGTH);
	printf("attrib byte = %x\n", attrib_byte);


	// skip lfn
	while(((attrib_byte&VFAT_ATTR_LFN) != 0)
			&& (increment_dir_descr(dir)!=0)) {
		printf("skipping lfn...\n");
		attrib_byte = GET_ENTRY_FIELD(dir, ATTRIB_OFFSET, ATTRIB_LENGTH);
	}

	// check validity
	if ((attrib_byte&VFAT_ATTR_INVAL) != 0) {
		// do nothing and go to next
		// if we can increment dir, then we try to read the next dir entry, return 0 else.
		printf("invalid attribute\n");
		return increment_dir_descr(dir) && vfat_readdir(dir, filler, fillerdata);
	}
/*
	// parse long file name
	if ((attrib_byte&VFAT_ATTR_LFN) == VFAT_ATTR_LFN) {
		name = read_lfn(dir);
	}
*/

	// parse info
	read_dir_entry(dir, &e);

	// store info in st

	struct stat st;
	memset(&st, 0, sizeof(st));
	st.st_uid = mount_uid;
	st.st_gid = mount_gid;
	st.st_nlink = 1;

	st.st_size = e.size;

	make_timespec(&st.st_atim, e.atime_date, 0, 0);
	make_timespec(&st.st_mtim, e.mtime_date, e.mtime_time, 0);
	make_timespec(&st.st_ctim, e.ctime_date, e.ctime_time, e.ctime_time);
	st.st_mode = (e.attr & VFAT_ATTR_DIR) ? S_IFDIR : S_IFREG;
	st.st_ino = (e.cluster_hi<<(CLUSHI_LENGTH*8)) + e.cluster_lo;


	// interprets short file name
	if (name == NULL) {
		name = malloc(13*sizeof(char));
		interpret_sfn(e.name, e.ext, name);
		printf("sfn read: %s\n", name);
	}
	// store info in buffer
	int success = filler(fillerdata, name, &st, 0)==0;
	// Hope this doesn't affect fillerdata content
	free(name);

	printf("filler function used, success is %d\n", success);
	// increment dir_descr pointer if data was successfully added to buffer
	success = success && increment_dir_descr(dir);
	printf("dir_descr incremented, succes is %d\n", success);
	return (success);
}
/*
 * Takes a vfat_search_data, a name and a stat associated to this name.
 * If the name of search data match to name, then the content of the pointer
 * st in vaft_search_data will be replaced by the given stat.
 *
 *
 * TODO Look here for search_entry hint!!!
 * How to use :
 *
 * this can be seen like a filler function that only fills with entry
 * that have name corresponding to data->name
 *
 * we know the current directory represented by a
 * struct vfat_dir_descr dir;
 *
 * struct vfat_search_data sd;
 * sd.name = name_we_look_for;
 * vfat_readdir(&dir, vfat_search_entry, &sd);
 *
 * sd.found indicates success of search
 * sd.st->st_mode indicates if it's a directory or a file
 * ... DAMM nothing indicates first cluster
 * maybe...
 * sd.st->st_ino can be used to store cluster number
 *
 * we can construct the new dir_descr and iterate!!
 *
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
 *
 * path the path to be resolved
 * st file/dir datas that will contain found data. Unspecified when return 0
 * return 0 if data was found error number else
 *
 */
static int
vfat_resolve(const char *path, struct stat *st)
{
	printf("resolving path %s:\n", path);
	struct vfat_search_data sd;

	struct vfat_dir_descr curr_dir;
	// root dir initialisation
	curr_dir.start_cluster = 0;
	curr_dir.current_cluster = 0;
	curr_dir.de_index = 0;

	// root dir stat (what we can know)
	memset(st, 0, sizeof(*st));
	st->st_ino = 2;
	st->st_mode = S_IFDIR;

	// creates a copy of path to use strtok
	char *path_copy = malloc(strlen(path)*sizeof(char)+1);
	path_copy = strncpy(path_copy, path, sizeof(path));
	path_copy[sizeof(path)] = '\0';

	char *path_entry = strtok(path_copy, "/");

	/* if path = "/" (root dir) then
	 * path_entry == NULL
	 * root attrib already set
	 *
	 * Thus everything is OK
	 */
	while (path_entry != NULL) {
		printf("searching entry of name %s in inode %u\n", path_entry, curr_dir.current_cluster);
		// set search data we are searching in curr_dir
		sd.name = path_entry;
		sd.found = 0;
		// reset st fields
		memset(st, 0, sizeof(*st));
		sd.st = st;

		// search parsed_path entry in curr_dir
		// reads dir until sd.st is set or end of dir reached
		while(vfat_readdir(&curr_dir, vfat_search_entry, &sd));
		// sd.found updated, corresponding stat stored in sd.st

		// go to next level of path
		path_entry = strtok(NULL, "/");

		// fail if path not found or entry found is not dir and end of path not reached
		if (!sd.found) {
			return ENOENT;
		}
		if (path_entry!=NULL && !S_ISDIR(sd.st->st_mode)) {
			return ENOTDIR;
		}

		if (path_entry!=NULL) {
			// update curr_dir to next found dir
			// start cluster of data = fat entry index - 2
			curr_dir.start_cluster = sd.st->st_ino - 2;
			reset_dir_descr(&curr_dir);
		}
	}

	free(path_copy);

	return 0;
}

static int
vfat_fuse_getattr(const char *path, struct stat *st)
{
	/*
	 * - find directory of file
	 * - looks for all dir entry in dir
	 * - stat is filled with corresponding direntry.
	 */
//	printf("vfat_fuse_getattr with path %s\n", path);
	return -vfat_resolve(path, st);
}

/*
 * return negated error number, 0 if ok
 */
static int
vfat_fuse_readdir(const char *path, void *data,
		  fuse_fill_dir_t filler, off_t offs, struct fuse_file_info *fi)
{
	printf("readdir with path %s\n", path);
	if (path==NULL || path[0]=='\0')
		return -ENOENT;
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

	/*
	 * Important note :
	 *
	 * we can simply ignore offset and use 0 wherever
	 * offset is used (filler function especially)
	 *
	 * If we want to use it, we have to transfer it in vfat_dir_descr
	 * into corresponding indexes
	 *
	 */

	// resolve path
	struct stat search_st;
	printf("resolving path %s...\n", path);
	int resolve_error = vfat_resolve(path, &search_st);
	if (resolve_error!=0)
		return -resolve_error;

	// check resolved st is a directory
	if(!S_ISDIR(search_st.st_mode))
		return -ENOTDIR;

	// read dir
	struct vfat_dir_descr dir_to_read;
	dir_to_read.start_cluster = search_st.st_ino;
	reset_dir_descr(&dir_to_read);
	printf("reading dir with inode %u\n", dir_to_read.current_cluster);
	while(vfat_readdir(&dir_to_read, filler, data));
	printf("read dir finished\n");
	return 0;
}

/*
 * TODO implement vfat_fuse_read
 */
static int
vfat_fuse_read(const char *path, char *buf, size_t size, off_t offs,
	       struct fuse_file_info *fi)
{
	printf("vfat_fuse_read\n");
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
