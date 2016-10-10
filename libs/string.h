#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_
#include "types.h"

char * int2str(uint32_t n, uint8_t type);

// 从 src 中拷贝 len 个字符到 dest
void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len);

// 将dest中前 len 个字符设置为 val
void memset(uint8_t *dest, const uint8_t val, uint32_t len);

// 前len 个设置为0
void bzero(uint8_t *dest, uint32_t len);

// 比较是否全部相等
int strcmp(const char *str1, const char *str2);

// 替换dest 为 src, 确保 dest 长度够
char *strcpy(char *dest, const char *src);

// 链接 dest 和 src,确保 dest 长度够
char *strcat(char *dest, const char *src);

// len str
int strlen(const char *src);

#endif 	// INCLUDE_TYPES_H_
