#include "types.h"
#include "console.h"
#include "stdio.h"
#include "debug.h"
#include "i386.h"

int kern_init(){
    console_init();
    printf("func \"kernel_init\" address: %p \n", kern_init);
    print_stab();
    printf ("--*-- print trace --*--\n");
    unsigned int ebp = read_ebp();
    unsigned int eip = *((unsigned int *)ebp + 1);
    printf("%x,%x \n",ebp,eip);
    grade_backtrace();

    while (1);
    return 0;
}
