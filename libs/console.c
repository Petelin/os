#include "console.h"
#include "types.h"
#include "i386.h"

// VGA 的显示缓冲的起点是 0xB8000
static uint16_t *video_memory = (uint16_t *)0xB8000;
// 屏幕光标的坐标""
static int8_t cs_x = 0;
static int8_t cs_y = 0;

void console_init(){
    console_clear();
}

void get_cursor(){
    uint16_t cursorLocation;
    outb(0x3d4, 0x0e); //索引寄存器，选择光标位置高位寄存器
    cursorLocation = inb(0x3d5) << 8; //取出光标位置高位字节
    outb(0x3d4, 0x0f); //索引寄存器，选择光标位置低位寄存器
    cursorLocation |= inb(0x3d5); //取出光标位置低位字节
    cs_x = cursorLocation % 80;
    cs_y = cursorLocation / 80;
}

static void move_cs(){
    // 屏幕是 80 字节宽
    uint16_t cursorLocation = cs_y * 80 + cs_x;
    // 在这里用到的两个内部寄存器的编号为与,分别表示光标位置1415
    outb(0x3D4, 14);
    outb(0x3D5, cursorLocation >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursorLocation);
}


void console_clear(){
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);
    int i;
    for (i = 0; i < 80 * 25; i++) {
        video_memory[i] = blank;
    }
    cs_x =0;cs_y=0;move_cs();
}


void console_putc_color(char c, real_color_t back, real_color_t fore){
    back = (uint8_t)back;
    fore = (uint8_t)fore;
    switch (c) {
        case 0x08:
            cs_x--;
            break;
        case 0x09:
            cs_x = cs_x & 0b1000;
            break;
        case '\r':
            cs_x=0;
            break;
        case '\n':
            cs_x=0;
            cs_y++;
            break;
        default:
            *(video_memory + cs_x+80*cs_y) = (((back << 4) | (fore & 0x0F)) << 8) | c;
            cs_x++;
            break;
    }
    // 每 80 个字符一行,满就必须换行了80
    if (cs_x >= 80) {
        cs_x = 0;
        cs_y++;
    }
    move_cs();
}


// 屏幕打印一个以 \0 结尾的字符串默认黑底白字
void console_write(char *cstr){
    console_write_color(*cstr,rc_black,rc_white);
}

// 屏幕打印一个以 \0 结尾的字符串带颜色
void console_write_color(char *cstr, real_color_t back, real_color_t fore){
    while (*cstr != '\0') {
        console_putc_color(*cstr,back,fore);
    }
}

// 屏幕输出一个十六进制的整型数
void console_write_hex(uint32_t n, real_color_t back, real_color_t fore){
}


// 屏幕输出一个十进制的整型数
void console_write_dec(uint32_t n, real_color_t back, real_color_t fore){
    char tmp[11];
    int32_t i = 0;
    if (n == 0) {
        console_putc_color('0',back,fore);
    }
    while(n > 0){
        tmp[i++] = n % 10 + 48;
        n /= 10;
    }
    for (;i>0;i--) {
        console_putc_color(tmp[i-1],back,fore);
    }
}
