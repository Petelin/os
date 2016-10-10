#include "types.h"
#include "console.h"
#include "stdio.h"
#include "debug.h"
#include "i386.h"
#include "idt.h"

int kern_init(){
    // 清屏
    console_clear();


    // 打印符号表
    print_stab();

    // 打印函数调用栈
    grade_backtrace();

    //初始化中断
    init_idt();

    // 清屏+打印
    console_init();

    int a = 1/0;
    asm volatile ("int $0x3");

    while (1);
    return 0;
}
