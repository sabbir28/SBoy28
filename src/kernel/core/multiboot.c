#include <stddef.h>
#include "kernel/multiboot.h"

static inline bool mb_flag(const multiboot_info_t *mbd, uint32_t bit)
{
    return (mbd != NULL) && (mbd->flags & bit);
}

/* -------------------------
 * Memory information
 * ------------------------- */

uint32_t mb_get_mem_lower(const multiboot_info_t *mbd)
{
    return mb_flag(mbd, 0x1) ? mbd->mem_lower : 0;
}

uint32_t mb_get_mem_upper(const multiboot_info_t *mbd)
{
    return mb_flag(mbd, 0x1) ? mbd->mem_upper : 0;
}

/* -------------------------
 * Boot device (raw + granular)
 * ------------------------- */

uint32_t mb_get_boot_device(const multiboot_info_t *mbd)
{
    return mb_flag(mbd, 0x2) ? mbd->boot_device : 0;
}

uint8_t mb_get_boot_drive(const multiboot_info_t *mbd)
{
    return mb_flag(mbd, 0x2) ?
        (uint8_t)((mbd->boot_device >> 24) & 0xFF) : 0;
}

uint8_t mb_get_boot_partition(const multiboot_info_t *mbd)
{
    return mb_flag(mbd, 0x2) ?
        (uint8_t)((mbd->boot_device >> 16) & 0xFF) : 0;
}

uint8_t mb_get_boot_subpartition(const multiboot_info_t *mbd)
{
    return mb_flag(mbd, 0x2) ?
        (uint8_t)((mbd->boot_device >> 8) & 0xFF) : 0;
}

/* -------------------------
 * Memory-map metadata
 * ------------------------- */

uint32_t mb_get_mmap_length(const multiboot_info_t *mbd)
{
    return mb_flag(mbd, 0x40) ? mbd->mmap_length : 0;
}

uint32_t mb_get_mmap_addr(const multiboot_info_t *mbd)
{
    return mb_flag(mbd, 0x40) ? mbd->mmap_addr : 0;
}
