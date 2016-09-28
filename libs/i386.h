#ifndef INCLUDE_ASM_H_
#define INCLUDE_ASM_H_
#include "types.h"

void outb(uint16_t port, uint8_t value);

uint8_t inb(uint16_t port);

uint16_t inw(uint16_t port);

inline void outb(uint16_t port, uint8_t value){
    asm volatile ("outb %1, %0" : : "dN"(port), "a"(value));
}

inline uint8_t inb(uint16_t port){
    uint8_t value;
    asm volatile ("inb %1, %0": "=a"(value): "dN"(port));
    return value;
}

inline uint16_t inw(uint16_t port){
    uint16_t value;
    asm volatile ("inw %1, %0": "=a"(value): "dN"(port));
    return value;
}

#endif
