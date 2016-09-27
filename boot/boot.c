#include <types.h>
#include <io.h>

int bootmain(){
    clean_concole();
    _putline("hello kernel.",0,0);
    _putline("it is difficult for me,but i like it.",2,0);
    _putline("i get time, it is a life thing !",4,0);
    return 0;
}
