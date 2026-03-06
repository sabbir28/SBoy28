#include "drivers/keyboard.h"
#include "common/ports.h"
//#include <stdint.h>

static uint8_t key_buffer[256];  // Buffer to store pressed keys
static int buffer_index = 0;           // Index to track buffer position

static int shift_pressed = 0;
static int ctrl_pressed = 0;
static int alt_pressed = 0;

// Initialize the keyboard (enable keyboard interrupt in the PIC)
void init_keyboard() {
    // In a real OS, you would also enable keyboard interrupts here.
    // For now, we're polling the keyboard directly.
}

// Read scancode from the keyboard input buffer (0x60 port)
uint8_t read_key() {
    return inb(0x60);  // Read from the keyboard data port
}

// Check if a key has been pressed
int is_key_pressed() {
    return inb(0x64) & 0x01;  // Check if the output buffer is ready to be read
}

// Poll the keyboard for keypresses
void poll_keyboard() {
    if (is_key_pressed()) {
        int scancode = (int)read_key();

        // Handle special keys (Shift, Ctrl, Alt)
        if (scancode == KEY_SHIFT_LEFT || scancode == KEY_SHIFT_RIGHT) {
            shift_pressed = 1;
        } else if (scancode == KEY_CTRL_LEFT || scancode == KEY_CTRL_RIGHT) {
            ctrl_pressed = 1;
        } else if (scancode == KEY_ALT_LEFT || scancode == KEY_ALT_RIGHT) {
            alt_pressed = 1;
        } else if (scancode == (KEY_SHIFT_LEFT + 0x80) || scancode == (KEY_SHIFT_RIGHT + 0x80)) {
            shift_pressed = 0;
        } else if (scancode == (KEY_CTRL_LEFT + 0x80) || scancode == (KEY_CTRL_RIGHT + 0x80)) {
            ctrl_pressed = 0;
        } else if (scancode == (KEY_ALT_LEFT + 0x80) || scancode == (KEY_ALT_RIGHT + 0x80)) {
            alt_pressed = 0;
        } else {
            key_buffer[buffer_index++] = (uint8_t)scancode;
        }
    }
}

// Get the latest key from the buffer
uint8_t get_key() {
    if (buffer_index > 0) {
        uint8_t key = key_buffer[0];
        for (int i = 0; i < buffer_index - 1; i++) {
            key_buffer[i] = key_buffer[i + 1];  // Shift the buffer
        }
        buffer_index--;  // Reduce the buffer size
        return key;
    }
    return 0;  // Return 0 if no key is pressed
}

