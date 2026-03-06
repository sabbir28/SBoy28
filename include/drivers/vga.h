#ifndef VGA_H
#define VGA_H

#include "kernel/types.h"
#include "ui/colors.h"

#define VGA_ADDRESS 0xA0000
#define VGA_WIDTH 320
#define VGA_HEIGHT 200

void vga_init(void);
void vga_put_pixel(uint32_t x, uint32_t y, uint8_t color);
void vga_clear(uint8_t color);
void vga_draw_char(uint32_t x, uint32_t y, char ch, uint8_t color);
void vga_draw_string(uint32_t x, uint32_t y, const char* str, uint8_t color);
void vga_render(void);
uint8_t vga_get_pixel(uint32_t x, uint32_t y);

#endif
