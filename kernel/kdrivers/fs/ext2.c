#include "ext2.h"

ext2_superblock *superblock;

ext2_superblock readSuperBlock()
{
    uint8_t data[1024];
    read_sectors_ATA_PIO(&data, 0, 2);
    ext2_superblock block;
    /* Yes, I did this by my own by hands (just consulting a table & ext2.h) */
    block.nInode = toUnsignedInt32(getDataBetweenRange(data, 0, 3));
    block.nBlock = toUnsignedInt32(getDataBetweenRange(data, 4, 7));
    block.nBlockSuperUser = toUnsignedInt32(getDataBetweenRange(data, 8, 11));
    block.nUnallocBlock = toUnsignedInt32(getDataBetweenRange(data, 12, 15));
    block.nUnallocInode = toUnsignedInt32(getDataBetweenRange(data, 16, 19));
    block.nBlockSuperBlockPos = toUnsignedInt32(getDataBetweenRange(data, 20, 23));
    block.nShiftLeftBlockSize = toUnsignedInt32(getDataBetweenRange(data, 24, 27));
    block.nShiftLeftFragmentSize = toUnsignedInt32(getDataBetweenRange(data, 28, 31));
    block.nBlockBlockGroup = toUnsignedInt32(getDataBetweenRange(data, 32, 35));
    block.nFragmentBlockGroup = toUnsignedInt32(getDataBetweenRange(data, 36, 39));
    block.nInodeBlockGroup = toUnsignedInt32(getDataBetweenRange(data, 40, 43));
    block.lastMountTimePOSIX = toUnsignedInt32(getDataBetweenRange(data, 44, 47));
    block.lastWrittenTimePOSIX = toUnsignedInt32(getDataBetweenRange(data, 48, 51));
    block.nTimesVolumeMountedSinceConsistencyCheck = toUnsignedInt16(getDataBetweenRange(data, 52, 53));
    block.nMountAllowedBeforeConsistencyCheck = toUnsignedInt16(getDataBetweenRange(data, 54, 55));
    block.ext2Signature = toUnsignedInt16(getDataBetweenRange(data, 56, 57));
    block.fileSystemState = toUnsignedInt16(getDataBetweenRange(data, 58, 59));
    block.whenErrorDetected = toUnsignedInt16(getDataBetweenRange(data, 60, 61));
    block.minorVersion = toUnsignedInt16(getDataBetweenRange(data, 62, 63));
    block.lastConsistencyCheckTimePOSIX = toUnsignedInt32(getDataBetweenRange(data, 64, 67));
    block.intervalBetweenForcedConsistencyCheck = toUnsignedInt32(getDataBetweenRange(data, 68, 71));
    block.creatorOperatingSystemID = toUnsignedInt32(getDataBetweenRange(data, 72, 75));
    block.userIDReservedBlocks = toUnsignedInt16(getDataBetweenRange(data, 80, 81));
    block.groupIDReservedBlocks = toUnsignedInt16(getDataBetweenRange(data, 82, 83));
    block.firstNonReservedInodeInFileSystem = toUnsignedInt32(getDataBetweenRange(data, 84, 87));
    block.sizeofEachInode = toUnsignedInt16(getDataBetweenRange(data, 88, 89));
    block.blockGroupSuperblock = toUnsignedInt16(getDataBetweenRange(data, 90, 91));
    block.optionalFeaturesPresent = toUnsignedInt32(getDataBetweenRange(data, 92, 95));
    block.requiredFeaturesPresent = toUnsignedInt32(getDataBetweenRange(data, 96, 99));
    block.notsupportedFeatures = toUnsignedInt32(getDataBetweenRange(data, 100, 103));
    memcpy(block.fileSystemID, getDataBetweenRange(data, 104, 119), sizeof(block.fileSystemID)); 
    memcpy(block.volumeName, getDataBetweenRange(data, 120, 135), sizeof(block.volumeName));
    memcpy(block.volumePath, getDataBetweenRange(data, 136, 199), sizeof(block.volumePath));
    block.compressionAlgorithm = toUnsignedInt32(getDataBetweenRange(data, 200, 203));
    block.nPreallocateBlocksFile = data[204];
    block.nPreallocateBlocksDirectory = data[205];
    block.___UNUSED___ = toUnsignedInt16(getDataBetweenRange(data, 206, 207));
    memcpy(block.journalID, getDataBetweenRange(data, 208, 233), sizeof(block.journalID));
    block.journalInode = toUnsignedInt32(getDataBetweenRange(data, 224, 227));
    block.journalDevice = toUnsignedInt32(getDataBetweenRange(data, 228, 231));
    block.headOrphanInodeList = toUnsignedInt32(getDataBetweenRange(data, 232, 235));
    memcpy(block.___UNUSED____, getDataBetweenRange(data, 236, 1023), sizeof(block.___UNUSED____));
    return block;
}

block_group_descriptor *whatBlockGroupContainInode(inode *the, ext2_superblock *superblock)
{
    block_group_descriptor *group = ((unsigned) the - 1) / superblock->nInodeBlockGroup; 
    return group;
}

unsigned findInodeInBlockGroup(inode *the, ext2_superblock *superblock)
{
    unsigned index = ((unsigned) the - 1) % superblock->nInodeBlockGroup;
    block_group_descriptor *containing = (index * superblock->sizeofEachInode) / superblock->nShiftLeftBlockSize;
    return (unsigned) containing;
}

IFILE *ifopen(inode *i)
{
    size_t sizeEachBlock = superblock->sizeofEachInode;
    uint32_t nBlocksGroup = superblock->nInodeBlockGroup;
    block_group_descriptor *group = whatBlockGroupContainInode(
                i,
                superblock
    );

    
}