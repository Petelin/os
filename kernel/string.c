# include "types.h"
# include "string.h"

// 制定位数返回结果字符数组
char * int2str(uint32_t n, uint8_t type){
    char table[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    static char tmp[64];
    int i = 0;
    if (n == 0) {
        tmp[i++] = '0';
    }
    while(n > 0){
        tmp[i++] = table[n % type];
        n /= type;
    }
    tmp[i] = '\0';
    // 反转
    char total = --i;
    for (;i > (total / 2); i--){
        char t = tmp[i];
        tmp[i] = tmp[total - i];
        tmp[total-i] = t;
    }
    return tmp;
}

void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len){
    while(--len > 0){
        *(dest + len) = *(src +len);
    }
}

void memset(uint8_t *dest, const uint8_t c, uint32_t len){
    while(--len > 0){
        *(dest + len) = c;
    }
}

void bzero(uint8_t *dest, uint32_t len){
    memset(dest, 0, len);
}

int strcmp(const char *str1, const char *str2){
    while(*str1++ == *str2++);
    if (*--str1 == '\0'){
        return TRUE;
    }else{
        return FALSE;
    }
}

char *strcpy(char *dest, const char *src){
    memcpy((uint8_t *)dest, (const uint8_t *)src, strlen(src));
    return dest;
}

// 追加一个字符
char *strcat(char *dest, const char *src){
    int i;
    for (i=0;*(dest + i) != '\0';i++);

    while(*src != '\0'){
        *(dest + i++) = *src++;
    }
    *(dest+i) = '\0';
    return dest;
}

int strlen(const char *s){
    int i;
    for(i=0;*s++ != '\0';i++);
    return i;
}
