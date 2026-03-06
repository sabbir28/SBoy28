ENTRY(_start)

SECTIONS
{
    /* The kernel will live at 64KB (0x10000) */
    . = 0x10000;

    .text : ALIGN(4K)
    {
        *(.text)
    }

    /* Read-only data */
    .rodata : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data : ALIGN(4K)
    {
        *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    _sbss = .;
    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
    _ebss = .;

    /* The compiler might produce other sections, by default include them here */
    /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame)
        *(.note.gnu.build-id)
    }
}
