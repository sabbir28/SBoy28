#include <stdint.h>
#include "common/ports.h"
#include "kernel/idt.h"
#include "drivers/pit.h"

extern void scheduler_tick_from_irq(void);

/* initialize PIT to 'hz' interrupts per second */
void pit_init(uint32_t hz)
{
    if (hz == 0) hz = 100; /* safe default */

    uint32_t divisor = 1193182 / hz;
    uint8_t l = divisor & 0xFF;
    uint8_t h = (divisor >> 8) & 0xFF;

    /* mode 3, lobyte/hibyte, channel 0 */
    outb(0x43, 0x36);
    outb(0x40, l);
    outb(0x40, h);

    /* Unmasking IRQ0 is handled by PIC initialization in idt.c */
}

/* Called from IDT (Interrupt 32) */
static void pit_irq_handler(registers_t *regs)
{
    (void)regs;
    scheduler_tick_from_irq();
}

void init_pit(uint32_t hz) {
    pit_init(hz);
    register_interrupt_handler(32, pit_irq_handler);
}
