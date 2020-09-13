#ifndef EXT2_H
#define EXT2_H

#include "../ata/ata.h"

/* Structure defining an EXT2 Superblock. */
typedef struct __superblock__t
{

    uint32_t nInode;
    uint32_t nBlock;
    uint32_t nBlockSuperUser;
    uint32_t nUnallocBlock;
    uint32_t nUnallocInode;
    uint32_t nBlockSuperBlockPos;
    uint32_t nShiftLeftBlockSize;
    uint32_t nShiftLeftFragmentSize;
    uint32_t nBlockBlockGroup;
    uint32_t nFragmentBlockGroup;
    uint32_t nInodeBlockGroup;
    uint32_t lastMountTimePOSIX;
    uint32_t lastWrittenTimePOSIX;
    uint16_t nTimesVolumeMountedSinceConsistencyCheck;
    uint16_t nMountAllowedBeforeConsistencyCheck;
    uint16_t ext2Signature;
    uint16_t fileSystemState;                         /* 1 = Clean, 2 = Error */
    uint16_t whenErrorDetected;                       /* 1 = Ignore, 2 = Remount to read-only, 3 = Kernel Panic */
    uint16_t minorVersion;
    uint32_t lastConsistencyCheckTimePOSIX;
    uint32_t intervalBetweenForcedConsistencyCheck;
    uint32_t creatorOperatingSystemID;                /* 0 = Linux, 1 = Hurd, 2 = MASIX, 3 = FreeBSD, 4 = Other "Lites", 5 = OS */
    uint32_t majorVersion;                            /* 1 = Will Enable Extended Superblock Fields */
    uint16_t userIDReservedBlocks;
    uint16_t groupIDReservedBlocks;

    /* Extended Superblock fields */
    uint32_t firstNonReservedInodeInFileSystem;
    uint16_t sizeofEachInode;
    uint16_t blockGroupSuperblock;
    uint32_t optionalFeaturesPresent;                 /* (see wiki.osdev.org/Ext2 -> Optional Feature Flags) */
    uint32_t requiredFeaturesPresent;                 /* 0x1 = Compression used, 0x2 = Directory entries contain type field, 0x4 = Replay
                                                       journal, 0x8 = filesystem uses a journal device */
    uint32_t notsupportedFeatures;
    uint8_t  fileSystemID[16];
    uint8_t  volumeName[16];
    uint8_t  volumePath[64];
    uint32_t compressionAlgorithm;
    uint8_t  nPreallocateBlocksFile;
    uint8_t  nPreallocateBlocksDirectory;
    uint16_t ___UNUSED___;
    uint8_t  journalID[16];
    uint32_t journalInode;
    uint32_t journalDevice;
    uint32_t headOrphanInodeList;
    uint8_t  ___UNUSED____[788];

} ext2_superblock;

/* Structure defining a EXT2 Block Group Descriptior. */
typedef struct blockgroup_descriptor_t
{

    uint32_t blockAddressOfBlockUsageBitmap;
    uint32_t blockAddressOfInodeUsageBitmap;
    uint32_t startingBlockAddressInodeTable;
    uint16_t nUnallocatedBlocksInGroup;
    uint16_t nUnallocatedInodesInGroup;
    uint16_t nDirectoriesInGroup;
    uint8_t  ___UNUSED___[14];

} block_group_descriptor;

typedef struct inode_t
{

    uint16_t typePermissions;
    uint16_t userID;
    uint32_t lowerSize;
    uint32_t lastAccessTimePOSIX;
    uint32_t creationTimePOSIX;
    uint32_t lastModificationTimePOSIX;
    uint32_t deletionTimePOSIX;
    uint16_t groupID;
    uint16_t countHardLinks;
    uint32_t countDiskSectorsUsed; /* Contains only the number of disk sectors used by the content, not the Inode structure itself. */
    uint32_t flags;
    uint32_t osSpecificValue;
    
    /* Direct Block Pointers */
    uint32_t dbp0; /* Direct Block Pointer */
    uint32_t dbp1;
    uint32_t dbp2;
    uint32_t dbp3;
    uint32_t dbp4;
    uint32_t dbp5;
    uint32_t dbp6;
    uint32_t dbp7;
    uint32_t dbp8;
    uint32_t dbp9;
    uint32_t dbp10;
    uint32_t dbp11;

    uint32_t singlyIndirectBlockPointer;
    uint32_t doublyIndirectBlockPointer;
    uint32_t triplyIndirectBlockPointer;
    uint32_t generationNumber;
    uint32_t extendedAttributeBlock;
    uint32_t filesize;
    uint32_t blockAddressOfFragment;
    uint32_t osSpecificValue2[3];

} inode;

ext2_superblock readSuperBlock();

typedef struct internal_directory
{

    uint32_t inode;
    uint16_t sizeOfEntry;
    uint8_t  nameLength;
    uint8_t  typeIndicator;
    uint8_t* nameCharacters; /* IMPORTANT : Reallocate to N (www.wiki.osdev.org/Ext2#Directory Entry) */

} idirectory;

typedef struct IFILE_T
{

    uint64_t tellData;

    inode Inode;

} IFILE;

void setSuperBlock(ext2_superblock *superblock);

IFILE *ifopen(const char* path);

#endif