#include "iso.h"

BootSector g_BootSector;
uint8_t* g_Fat = 0;
DirectoryEntry* g_RootDirectory = 0;
uint32_t g_RootDirectoryEnd = 0;
RAMDisk g_ramdisk;

// simple memcpy/memcmp
void* kmemcpy(void* dest, const void* src, uint32_t n) {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;
    for (uint32_t i = 0; i < n; i++) d[i] = s[i];
    return dest;
}

int kmemcmp(const void* a, const void* b, uint32_t n) {
    const uint8_t* x = (const uint8_t*)a;
    const uint8_t* y = (const uint8_t*)b;
    for (uint32_t i = 0; i < n; i++)
        if (x[i] != y[i]) return x[i] - y[i];
    return 0;
}

// RAMDisk operations
bool readBootSectorRAM(RAMDisk* disk) {
    if (disk->size < sizeof(BootSector)) return false;
    kmemcpy(&g_BootSector, disk->base, sizeof(BootSector));
    return true;
}

bool readSectorsRAM(RAMDisk* disk, uint32_t lba, uint32_t count, void* bufferOut, uint16_t bytesPerSector) {
    uint32_t offset = lba * bytesPerSector;
    uint32_t len = count * bytesPerSector;
    if (offset + len > disk->size) return false;
    kmemcpy(bufferOut, disk->base + offset, len);
    return true;
}

bool readFatRAM(RAMDisk* disk) {
    g_Fat = disk->base + g_BootSector.ReservedSectors * g_BootSector.BytesPerSector;
    return true;
}

bool readRootDirectoryRAM(RAMDisk* disk) {
    uint32_t lba = g_BootSector.ReservedSectors + g_BootSector.SectorsPerFat * g_BootSector.FatCount;
    uint32_t size = sizeof(DirectoryEntry) * g_BootSector.DirEntryCount;
    uint32_t sectors = (size + g_BootSector.BytesPerSector - 1) / g_BootSector.BytesPerSector;
    g_RootDirectoryEnd = lba + sectors;
    g_RootDirectory = (DirectoryEntry*)(disk->base + lba * g_BootSector.BytesPerSector);
    return true;
}

bool readFileRAM(DirectoryEntry* fileEntry, RAMDisk* disk, uint8_t* outputBuffer) {
    if (!fileEntry || !outputBuffer) return false;

    uint16_t cluster = fileEntry->FirstClusterLow;
    uint32_t remaining = fileEntry->Size;

    while (cluster < 0x0FF8 && remaining > 0) {
        uint32_t lba = g_RootDirectoryEnd + (cluster - 2) * g_BootSector.SectorsPerCluster;
        uint32_t bytesToRead = g_BootSector.SectorsPerCluster * g_BootSector.BytesPerSector;
        if (bytesToRead > remaining) bytesToRead = remaining;

        kmemcpy(outputBuffer, disk->base + lba * g_BootSector.BytesPerSector, bytesToRead);

        outputBuffer += bytesToRead;
        remaining -= bytesToRead;

        uint32_t fatIndex = cluster + (cluster / 2);
        uint16_t nextCluster;
        if (cluster & 1)
            nextCluster = (*(uint16_t*)(g_Fat + fatIndex)) >> 4;
        else
            nextCluster = (*(uint16_t*)(g_Fat + fatIndex)) & 0x0FFF;
        cluster = nextCluster;
    }

    return true;
}

DirectoryEntry* findFile(const char* name) {
    for (uint32_t i = 0; i < g_BootSector.DirEntryCount; i++) {
        if (kmemcmp(name, g_RootDirectory[i].Name, 11) == 0)
            return &g_RootDirectory[i];
    }
    return 0;
}
