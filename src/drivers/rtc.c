#include "drivers/rtc.h"
#include "common/ports.h"

// Helper to convert BCD to binary
static int bcd_to_binary(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

int get_hours() {
    outb(0x70, 0x04);
    uint8_t hours = inb(0x71);
    return bcd_to_binary(hours);
}

int get_minutes() {
    outb(0x70, 0x02);
    uint8_t minutes = inb(0x71);
    return bcd_to_binary(minutes);
}

int get_seconds() {
    outb(0x70, 0x00);
    uint8_t seconds = inb(0x71);
    return bcd_to_binary(seconds);
}

// Function to get the current time as a string
char* get_current_time() {
    static char time_str[9]; // hh:mm:ss\0
    int hours, minutes, seconds;

    // Read RTC registers (your existing code)
    outb(0x70, 0x00);
    seconds = inb(0x71);
    outb(0x70, 0x02);
    minutes = inb(0x71);
    outb(0x70, 0x04);
    hours = inb(0x71);

    // Convert BCD to binary if necessary
    seconds = ((seconds / 16) * 10) + (seconds & 0x0F);
    minutes = ((minutes / 16) * 10) + (minutes & 0x0F);
    hours = ((hours / 16) * 10) + (hours & 0x0F);

    // Convert to string manually
    time_str[0] = '0' + (hours / 10);
    time_str[1] = '0' + (hours % 10);
    time_str[2] = ':';
    time_str[3] = '0' + (minutes / 10);
    time_str[4] = '0' + (minutes % 10);
    time_str[5] = ':';
    time_str[6] = '0' + (seconds / 10);
    time_str[7] = '0' + (seconds % 10);
    time_str[8] = '\0';

    return time_str;
}

void Sleep(int seconds) {
    // Get the current time in seconds
    // Note: This is a simple implementation and may not be accurate
    int start = get_seconds();
    int elapsed = 0;

    while (elapsed < seconds) {
        int current = get_seconds();

        // Handle RTC wrap-around from 59 to 0
        if (current < start) {
            elapsed = (60 - start) + current;
        } else {
            elapsed = current - start;
        }
    }
}
