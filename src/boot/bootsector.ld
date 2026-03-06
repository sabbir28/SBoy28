ENTRY(_start)

SECTIONS
{
    /* The bootloader is loaded at 0x7C00 by the BIOS */
    . = 0x7C00;

    .text :
    {
        *(.text)
    }

    /* Padding to 510 bytes (relative to 0x7C00) */
    . = 0x7C00 + 510;

    .sig :
    {
        SHORT(0xAA55)
    }
}
