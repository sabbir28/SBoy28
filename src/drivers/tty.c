#include "drivers/tty.h"
#include "drivers/vga.h"
#include "common/utils.h"

static uint32_t tty_column = 0;
static uint32_t tty_row = 0;
static uint8_t tty_fore_color = WHITE;
static uint8_t tty_back_color = BLUE;

// In 320x200, using 8x8 font, we have 40x25 characters
#define TTY_WIDTH 40
#define TTY_HEIGHT 25

void tty_init(void) {
    tty_column = 0;
    tty_row = 0;
    tty_fore_color = WHITE;
    tty_back_color = BLUE;
    vga_clear(tty_back_color);
}

void tty_set_color(uint8_t fore_color, uint8_t back_color) {
    tty_fore_color = fore_color;
    tty_back_color = back_color;
}

void tty_putchar(char c) {
    if (c == '\n') {
        tty_column = 0;
        tty_row++;
    } else {
        vga_draw_char(tty_column * 8, tty_row * 8, c, tty_fore_color);
        tty_column++;
        if (tty_column >= TTY_WIDTH) {
            tty_column = 0;
            tty_row++;
        }
    }
    
    if (tty_row >= TTY_HEIGHT) {
        // Simple scroll: just clear for now
        tty_row = 0;
        vga_clear(tty_back_color);
    }
}

void tty_putstring(const char* str) {
    for (uint32_t i = 0; str[i] != '\0'; i++) {
        tty_putchar(str[i]);
    }
}

void tty_print_at(uint32_t x, uint32_t y, const char* str) {
    // x and y are in character coordinates
    vga_draw_string(x * 8, y * 8, str, tty_fore_color);
}

void tty_clear(void) {
    vga_clear(tty_back_color);
    tty_column = 0;
    tty_row = 0;
}
