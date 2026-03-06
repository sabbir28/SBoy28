#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>
#include <stdbool.h>

// -----------------------------
// Multiboot info structure
// -----------------------------
typedef struct multiboot_info {
    uint32_t flags;          // Multiboot info flags

    // Memory info
    uint32_t mem_lower;      // Lower memory in KB
    uint32_t mem_upper;      // Upper memory in KB

    uint32_t boot_device;    // Boot device
    uint32_t cmdline;        // Kernel command line (ignored here)
    uint32_t mods_count;     // Module count
    uint32_t mods_addr;      // Module address

    uint32_t syms[4];        // ELF section info or a.out symbol table
    uint32_t mmap_length;    // Memory map length
    uint32_t mmap_addr;      // Memory map address

    uint32_t drives_length;  // Drives info length
    uint32_t drives_addr;    // Drives info address

    uint32_t config_table;   // ROM configuration table (unused)
    uint32_t boot_loader_name; // Bootloader string pointer
    uint32_t apm_table;      // APM table (unused)
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
} multiboot_info_t;

// -----------------------------
// Multiboot memory map entry
// -----------------------------
typedef struct multiboot_mmap_entry {
    uint32_t size;
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
} __attribute__((packed)) multiboot_mmap_entry_t;

// Multiboot module structure
typedef struct multiboot_module {
    uint32_t mod_start;  // Module start address
    uint32_t mod_end;    // Module end address
    uint32_t string;     // Module string pointer
    uint32_t reserved;   // Reserved
} __attribute__((packed)) multiboot_module_t;




// class names
/* Memory */
uint32_t mb_get_mem_lower(const multiboot_info_t *mbd);
uint32_t mb_get_mem_upper(const multiboot_info_t *mbd);

/* Boot Device */
uint32_t mb_get_boot_device(const multiboot_info_t *mbd);
uint8_t  mb_get_boot_drive(const multiboot_info_t *mbd);
uint8_t  mb_get_boot_partition(const multiboot_info_t *mbd);
uint8_t  mb_get_boot_subpartition(const multiboot_info_t *mbd);

/* Memory Map */
uint32_t mb_get_mmap_length(const multiboot_info_t *mbd);
uint32_t mb_get_mmap_addr(const multiboot_info_t *mbd);



#endif // MULTIBOOT_H
