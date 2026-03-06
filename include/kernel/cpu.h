#ifndef CPU_H
#define CPU_H

#include <stdint.h>

static inline void cli(void) {
    __asm__ volatile("cli");
}

static inline void sti(void) {
    __asm__ volatile("sti");
}

static inline uint32_t save_irq_state(void) {
    uint32_t flags;
    __asm__ volatile (
        "pushfl\n"
        "popl %0\n"
        "cli"
        : "=g"(flags)
        :
        : "memory"
    );
    return flags;
}

static inline void restore_irq_state(uint32_t flags) {
    __asm__ volatile (
        "pushl %0\n"
        "popfl"
        :
        : "g"(flags)
        : "memory", "cc"
    );
}

#endif // CPU_H
