#include <stdint.h>

typedef struct {
    const char* path;
    uint8_t* buffer;
    int fd;
} ELFReader;

// Assembly functions
extern void ELFReader_init(ELFReader* self, const char* path, uint8_t* buffer);
extern void ELFReader_read_header(ELFReader* self);
extern void ELFReader_print_header(ELFReader* self);

#include <stdio.h>
#include <stdlib.h>

int main() {
    uint8_t header[52];          // ELF header buffer
    ELFReader reader;

    ELFReader_init(&reader, "ATMOS.bin", header);
    ELFReader_read_header(&reader);
    ELFReader_print_header(&reader);

    printf("\nMagic bytes: ");
    for (int i = 0; i < 16; i++)
        printf("%02x ", header[i]);
    printf("\n");

    return 0;
}
