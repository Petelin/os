#ifndef _INCLUDE_STDIO_H_
#define _INCLUDE_STDIO_H_
#include "types.h"

void printf(const char *format, ...);

int vsprintf(char * buffer, const char * format,va_list args);

#endif
