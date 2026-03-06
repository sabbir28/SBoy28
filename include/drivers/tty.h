#ifndef TTY_H
#define TTY_H

#include "kernel/types.h"

void tty_init(void);
void tty_set_color(uint8_t fore_color, uint8_t back_color);
void tty_putchar(char c);
void tty_putstring(const char* str);
void tty_clear(void);
void tty_print_at(uint32_t x, uint32_t y, const char* str);

#endif
