    .section .text
    .global irq12_wrapper
    .extern mouse_irq_handler
    .extern irq_common_stub_end   /* optional common wrapper end if you use a shared stub */

    /* Simple IRQ wrapper that saves registers, calls C handler, restores and
       then executes IRET. Adapt to your kernel's ISR prologue/epilogue conventions. */

irq12_wrapper:
    cli
    pushal              /* push general purpose registers */
    push %ds
    push %es
    push %fs
    push %gs

    /* load kernel data segment if required by your kernel */
    /* mov $KERNEL_DS, %ax
       mov %ax, %ds
       mov %ax, %es
       mov %ax, %fs
       mov %ax, %gs
    */

    call mouse_irq_handler

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popal

    /* Send EOI: either your IRQ return sequence or rely on driver doing it.
       If your PIC EOI is handled here, do it with outb to 0xA0/0x20. */

    sti
    iret
