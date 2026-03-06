#ifndef RTC_H
#define RTC_H

#include "kernel/types.h"

int get_hours();
int get_minutes();
int get_seconds();
char* get_current_time();
void Sleep(int seconds);

#endif
