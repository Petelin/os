#include "types.h"
#include "console.h"

int kern_init(){
    console_init();
    console_putc_color('a', rc_black, rc_white);
    console_putc_color('a', rc_black, rc_white);
    console_putc_color('\n', rc_black, rc_white);
    console_write_dec(112390888881233331, rc_black, rc_white);
    while (1);
    return 0;
}
