#pragma once
#include <stdint.h>
#include <stddef.h>

typedef uint8_t bool;
#define true 1
#define false 0

typedef struct {
    uint8_t* base;
    uint32_t size;
} RAMDisk;

typedef struct __attribute__((packed)) {
    uint8_t BootJumpInstruction[3];
    uint8_t OemIdentifier[8];
    uint16_t BytesPerSector;
    uint8_t SectorsPerCluster;
    uint16_t ReservedSectors;
    uint8_t FatCount;
    uint16_t DirEntryCount;
    uint16_t TotalSectors;
    uint8_t MediaDescriptorType;
    uint16_t SectorsPerFat;
    uint16_t SectorsPerTrack;
    uint16_t Heads;
    uint32_t HiddenSectors;
    uint32_t LargeSectorCount;

    uint8_t DriveNumber;
    uint8_t _Reserved;
    uint8_t Signature;
    uint32_t VolumeId;
    uint8_t VolumeLabel[11];
    uint8_t SystemId[8];
} BootSector;

typedef struct __attribute__((packed)) {
    uint8_t Name[11];
    uint8_t Attributes;
    uint8_t _Reserved;
    uint8_t CreatedTimeTenths;
    uint16_t CreatedTime;
    uint16_t CreatedDate;
    uint16_t AccessedDate;
    uint16_t FirstClusterHigh;
    uint16_t ModifiedTime;
    uint16_t ModifiedDate;
    uint16_t FirstClusterLow;
    uint32_t Size;
} DirectoryEntry;

// globals
extern BootSector g_BootSector;
extern uint8_t* g_Fat;
extern DirectoryEntry* g_RootDirectory;
extern uint32_t g_RootDirectoryEnd;
extern RAMDisk g_ramdisk;

// kernel-only functions
bool readBootSectorRAM(RAMDisk* disk);
bool readFatRAM(RAMDisk* disk);
bool readRootDirectoryRAM(RAMDisk* disk);
bool readFileRAM(DirectoryEntry* fileEntry, RAMDisk* disk, uint8_t* outputBuffer);

DirectoryEntry* findFile(const char* name);

void* kmemcpy(void* dest, const void* src, uint32_t n);
int kmemcmp(const void* a, const void* b, uint32_t n);
