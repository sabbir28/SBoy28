#ifndef UI_H
#define UI_H

#include "kernel/types.h"

void draw_hline(uint32_t y, uint8_t fore_color, uint8_t back_color);
void draw_box_and_text(uint32_t box_width, uint32_t box_height, uint32_t box_x, uint32_t box_y, const char* text);
void print_at(uint32_t x, uint32_t y, const char* text, uint8_t fore_color, uint8_t back_color);
void clear_row(uint32_t y, uint8_t fore_color, uint8_t back_color);
void clear_col(uint32_t x, uint8_t fore_color, uint8_t back_color);
void clear_area(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t fore_color, uint8_t back_color);
void clear_full_screen(uint8_t fore_color, uint8_t back_color);
#endif
// UI_H
