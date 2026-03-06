#include "ui/ui.h"
#include "common/utils.h"
#include "drivers/vga.h"
#include "kernel/kernel.h"

// Adapted for 320x200 graphical mode (simple scaling or pixel-based)

void draw_hline(uint32_t y, uint8_t fore_color, uint8_t back_color) {
    (void)back_color; // Not used in simple hline
    for (uint32_t x = 0; x < VGA_WIDTH; x++) {
        vga_put_pixel(x, y, fore_color);
    }
}

void draw_box_and_text(uint32_t box_width, uint32_t box_height, uint32_t box_x, uint32_t box_y, const char* text) {
    // Convert to pixel coordinates if they were passed as character coords (8x8)
    // For now, assume they are pixel coordinates.
    
    // Draw horizontal lines
    for (uint32_t i = box_x; i < box_x + box_width; i++) {
        vga_put_pixel(i, box_y, WHITE);
        vga_put_pixel(i, box_y + box_height - 1, WHITE);
    }
    // Draw vertical lines
    for (uint32_t i = box_y; i < box_y + box_height; i++) {
        vga_put_pixel(box_x, i, WHITE);
        vga_put_pixel(box_x + box_width - 1, i, WHITE);
    }

    uint32_t text_len = strlen(text);
    uint32_t text_x = box_x + (box_width / 2) - (text_len * 4); // 8/2 = 4
    uint32_t text_y = box_y + (box_height / 2) - 4;
    
    vga_draw_string(text_x, text_y, text, YELLOW);
}

void print_at(uint32_t x, uint32_t y, const char* text, uint8_t fore_color, uint8_t back_color) {
    (void)back_color;
    vga_draw_string(x, y, text, fore_color);
}

void clear_row(uint32_t y, uint8_t fore_color, uint8_t back_color) {
    (void)fore_color;
    for (uint32_t x = 0; x < VGA_WIDTH; x++) {
        for(uint32_t dy=0; dy<8; dy++) {
            vga_put_pixel(x, y + dy, back_color);
        }
    }
}

void clear_col(uint32_t x, uint8_t fore_color, uint8_t back_color) {
    (void)fore_color;
    for (uint32_t y = 0; y < VGA_HEIGHT; y++) {
        for(uint32_t dx=0; dx<8; dx++) {
            vga_put_pixel(x + dx, y, back_color);
        }
    }
}

void clear_area(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t fore_color, uint8_t back_color) {
    (void)fore_color;
    for (uint32_t j = 0; j < height; j++) {
        for (uint32_t i = 0; i < width; i++) {
            vga_put_pixel(x + i, y + j, back_color);
        }
    }
}

void clear_full_screen(uint8_t fore_color, uint8_t back_color) {
    (void)fore_color;
    vga_clear(back_color);
}
