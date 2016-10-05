#include <stdio.h>
#include <types.h>
#include <console.h>
#include <string.h>

static char * format_to_str(const char *format, va_list args){
    static char buffer[1024];
    int i = vsprintf(buffer, format, args);
    buffer[i] = '\0';
    return buffer;
}


void printf(const char *format, ...){
    va_list args;
    va_start(args, format);
    console_write(format_to_str(format, args));
    va_end(args);
}

void cprintf(const char *format, real_color_t back, real_color_t fore, ...){
    va_list args;
    va_start(args, fore);
    console_write_color(format_to_str(format, args), back, fore);
    va_end(args);
}


int vsprintf(char * buffer, const char * format,va_list args){
    size_t i;
    int n;
    char * t;
    for (i = 0; *format != '\0'; i++) {
        if (*format == '%') {
            switch (*++format) {
                case 'c':
                    buffer[i] = (char)va_arg(args, int);
                    break;
                case 's':
                    t = (char *)va_arg(args, char *);
                    while (*t != '\0'){
                        buffer[i++] = *t++;
                    }
                    i--;
                    break;
                case 'd':
                    n = va_arg(args, int);
                    t = int2str(n,10);
                    while (*t != '\0'){
                        buffer[i++] = *t++;
                    }
                    i--;
                    break;
                case 'x':
                    n = va_arg(args, int);
                    t = int2str(n,16);
                    while (*t != '\0'){
                        buffer[i++] = *t++;
                    }
                    i--;
                    break;
                case 'p':
                    buffer[i++] = 'O';
                    buffer[i++] = 'x';
                    n = va_arg(args, int);
                    t = int2str(n,16);
                    uint16_t len = 8 - strlen(t);
                    while(len--){
                        buffer[i++]='0';
                    }
                    while (*t != '\0'){
                        buffer[i++] = *t++;
                    }
                    i--;
                    break;
                case '%':
                    buffer[i] = '%';
                    break;
            }
            format++;
        }else{
            buffer[i] = *format++;
        }
    }
    return i;
}
