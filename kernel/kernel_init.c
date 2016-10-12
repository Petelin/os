#include "types.h"
#include "console.h"
#include "stdio.h"
#include "debug.h"
#include "i386.h"
#include "idt.h"
#include "timer.h"

int kern_init(){
    // 清屏
    console_clear();

    // 打印符号表
    /*print_stab();*/

    // 打印函数调用栈
    grade_backtrace();

    //初始化中断
    init_idt();

    stop();
    timer_callback(0);

    // 初始化时钟硬件
    init_timer(10);

    // 开启中断
    asm volatile ("sti");

    // 清屏+打印
    console_init();

    while (1);
    return 0;
}
