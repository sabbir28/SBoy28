#include "kernel/kheap.h"

// Very simple bump allocator for now
// In a real OS, this would be a proper heap
static uint8_t kheap[1024 * 1024]; // 1MB heap
static uint32_t kheap_ptr = 0;

void* kmalloc(size_t size) {
    if (kheap_ptr + size > sizeof(kheap)) {
        return NULL; // Out of memory
    }
    void* res = &kheap[kheap_ptr];
    kheap_ptr += size;
    return res;
}

void kfree(void* p) {
    // Simple bump allocator doesn't support free
    (void)p;
}
