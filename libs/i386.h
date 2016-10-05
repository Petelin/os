#ifndef INCLUDE_ASM_H_
#define INCLUDE_ASM_H_
#include "types.h"

static inline void outb(uint16_t port, uint8_t value);

static inline uint8_t inb(uint16_t port);

static inline uint16_t inw(uint16_t port);

static inline uint32_t read_ebp() __attribute__((always_inline));


static inline void outb(uint16_t port, uint8_t value){
    asm volatile ("outb %1, %0" : : "dN"(port), "a"(value));
}

static inline uint8_t inb(uint16_t port){
    uint8_t value;
    asm volatile ("inb %1, %0": "=a"(value): "dN"(port));
    return value;
}

static inline uint16_t inw(uint16_t port){
    uint16_t value;
    asm volatile ("inw %1, %0": "=a"(value): "dN"(port));
    return value;
}

static inline uint32_t read_ebp(){
    uint32_t ebp;
    asm volatile("mov %%ebp, %0": "=r"(ebp));
    return ebp;
}

#endif
