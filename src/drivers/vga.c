#include "drivers/vga.h"
#include "ui/font_data.h"
#include "kernel/kheap.h"
#include "common/utils.h"
#include "kernel/spinlock.h"
#include <stdint.h>

static uint8_t* vga_mem = (uint8_t*)VGA_ADDRESS;
static uint8_t* vga_backbuffer = NULL;
static spinlock_t vga_lock;

void vga_init(void) {
    // Mode 13h is set in bootloader
    spinlock_init(&vga_lock);
    vga_backbuffer = (uint8_t*)kmalloc(VGA_WIDTH * VGA_HEIGHT);
    if (vga_backbuffer) {
        memset(vga_backbuffer, 0, VGA_WIDTH * VGA_HEIGHT);
    }
}

void vga_render(void) {
    if (!vga_backbuffer) return;
    memcpy(vga_mem, vga_backbuffer, VGA_WIDTH * VGA_HEIGHT);
}

void vga_put_pixel(uint32_t x, uint32_t y, uint8_t color) {
    if (x < VGA_WIDTH && y < VGA_HEIGHT && vga_backbuffer) {
        vga_backbuffer[y * VGA_WIDTH + x] = color;
    }
}

uint8_t vga_get_pixel(uint32_t x, uint32_t y) {
    if (x < VGA_WIDTH && y < VGA_HEIGHT && vga_backbuffer) {
        return vga_backbuffer[y * VGA_WIDTH + x];
    }
    return 0;
}

void vga_clear(uint8_t color) {
    if (!vga_backbuffer) return;
    spinlock_lock(&vga_lock);
    memset(vga_backbuffer, color, VGA_WIDTH * VGA_HEIGHT);
    spinlock_unlock(&vga_lock);
}

static void vga_draw_char_locked(uint32_t x, uint32_t y, char ch, uint8_t color) {
    if ((uint8_t)ch > 127) return;
    const uint8_t* glyph = font_8x8[(uint8_t)ch];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (glyph[i] & (1 << (7 - j))) {
                vga_put_pixel(x + j, y + i, color);
            }
        }
    }
}

void vga_draw_char(uint32_t x, uint32_t y, char ch, uint8_t color) {
    spinlock_lock(&vga_lock);
    vga_draw_char_locked(x, y, ch, color);
    spinlock_unlock(&vga_lock);
}

void vga_draw_string(uint32_t x, uint32_t y, const char* str, uint8_t color) {
    spinlock_lock(&vga_lock);
    while (*str) {
        vga_draw_char_locked(x, y, *str++, color);
        x += 8;
        if (x + 8 > VGA_WIDTH) {
            x = 0;
            y += 8;
        }
        if (y + 8 > VGA_HEIGHT) break;
    }
    spinlock_unlock(&vga_lock);
}
