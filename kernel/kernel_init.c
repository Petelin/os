#include "types.h"
#include "console.h"
#include "stdio.h"

int kern_init(){
    console_init();
    while (1);
    return 0;
}
