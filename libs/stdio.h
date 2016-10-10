#ifndef _INCLUDE_STDIO_H_
#define _INCLUDE_STDIO_H_
#include "types.h"
#include "console.h"

void printf(const char *format, ...);

void cprintf(const char *format, real_color_t back, real_color_t fore, ...);

int vsprintf(char * buffer, const char * format,va_list args);

#endif
