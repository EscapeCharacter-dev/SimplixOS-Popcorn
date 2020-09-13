#ifndef FAT32_H
#define FAT32_H

#include "../ata/ata.h"

typedef unsigned int uintptr_t;

typedef struct BPB_T
{

    uint8_t  disassembleJump[3];
    uint8_t  oemIndentifier[8];
    uint16_t nBytesSector;
    uint8_t  nSectorCluster;
    uint16_t nReservedSectors;
    uint8_t  nFAT;
    uint16_t nDirectories;
    uint16_t sectorsLogicalVolume;
    uint8_t  media_descriptor_type;
    uint16_t sectorsPerFAT16Lower;
    uint16_t nSectorsTrack;
    uint16_t nHeadSidesMedia;
    uint32_t nHiddenSectors;

    uint32_t nSectorsFAT;
    uint16_t flags;
    uint16_t FATVersion;
    uint32_t clusterNumberRoot;
    uint16_t sectorFSInfo;
    uint16_t backupBootSectorNumber;
    uint8_t  __RESERVED__[12];
    uint8_t  driverNumber;
    uint8_t  flagsWINNT;
    uint8_t  signature;
    uint32_t volumeSerialID;
    uint8_t  volumeLabel[11];
    uint8_t  systemIndentiferString[8];

    uint32_t firstUsableCluster;

} __attribute__((packed)) BPB;

typedef struct FSInfo_t
{

    uint32_t leadSignature;
    uint8_t  __RESERVED__[480];
    uint32_t anotherSignature;
    uint32_t lastKnownFreeClustor;
    uint32_t clusterNumberDriverStart;
    uint8_t  __RESERVED___[12];
    uint32_t trailSignature = 0xAA550000;

} __attribute__((packed)) FSInfo;

typedef struct DirectoryEntry_t
{

    uint8_t  name[8];
    uint8_t  ext[4];
    uint8_t  attrib;
    uint8_t  usrattrib;

    uint8_t  undelete;
    uint16_t creationTime;
    uint16_t creationDate;
    uint16_t accessDate;
    uint16_t clusterHigh;

    uint16_t modifiedTime;
    uint16_t modifiedDate;
    uint16_t clusterLow;
    uint32_t filesize;

} __attribute__((packed)) DirectoryEntry;

typedef struct FAT32_t
{

    BPB    *bpb;
    FSInfo *fsi;

} __attribute__((packed)) FAT32;

uint64_t FAT32_ClusterToLBA(uint32_t cluster, BPB *fs)
{
    return fs->firstUsableCluster + cluster * fs->nSectorCluster - (2 * fs->nSectorCluster);
}

uint64_t FAT32_GetStartLBA(BPB *fs)
{
    return FAT32_ClusterToLBA(fs->firstUsableCluster, fs);
}

BPB *createBPB(uint8_t *fat)
{
    BPB *the;

    the->nBytesSector             = *((uint16_t*)((uintptr_t) fat + 11));
    the->nSectorCluster           = *((uint8_t*)((uintptr_t) fat + 13));
    the->nReservedSectors         = *((uint16_t*)((uintptr_t) fat + 14));
    the->nFAT                     = *((uint8_t*)((uintptr_t) fat + 16));
    the->nDirectories             = *((uint16_t*)((uintptr_t) fat + 17));
    
    if ((uint16_t)(*((uint16_t*)(fat + 17))) > 0)
        the->sectorsLogicalVolume = *((uint16_t*)((uintptr_t) fat + 17));
    else
        the->sectorsLogicalVolume = *((uint32_t*)((uintptr_t) fat + 32));

    the->nHiddenSectors           = *((uint32_t*)((uintptr_t) fat + 28));
    
    the->nSectorsFAT              = *((uint32_t*)((uintptr_t) fat + 36));
    the->clusterNumberRoot        = *((uint32_t*)((uintptr_t) fat + 44));
    the->sectorFSInfo             = *((uint16_t*)((uintptr_t) fat + 48));

    the->backupBootSectorNumber   = *((uint16_t*)((uintptr_t) fat + 50));
    the->firstUsableCluster       = FAT32_GetStartLBA(the) + the->nReservedSectors
                                    + (the->nFAT * the->nSectorsFAT);
    

    return the;
}

#include "../../include/libc/string.h"

void Traverse(char *path)
{
    const char *pathparts = strtok(path, "\\/");

    FSObject
}

#endif