#ifndef KERNEL_H
#define KERNEL_H

#include "kernel/types.h"
#include "ui/colors.h"

// Redundant macros removed, moved to vga.h

extern uint16_t* vga_buffer;
extern uint8_t g_fore_color, g_back_color;
extern uint32_t vga_index;

void init_vga(uint8_t fore_color, uint8_t back_color);
void clear_vga_buffer(uint16_t **buffer, uint8_t fore_color, uint8_t back_color);
uint16_t vga_entry(unsigned char ch, uint8_t fore_color, uint8_t back_color);

void kernel_entry();

#endif
