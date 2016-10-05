#include <debug.h>
#include <stdio.h>
#include "i386.h"
#include "stab.h"
extern stab_t __STAB_BEGIN__[];  // beginning of stabs table
extern stab_t __STAB_END__[];    // end of stabs table
extern char __STABSTR_BEGIN__[];      // beginning of string table
extern char __STABSTR_END__[];

static stab_t *stabs;
static stab_t *stab_end;
static char *stabstr = __STABSTR_BEGIN__;
static char *stabstr_end = __STABSTR_END__;

struct stab * stab_bsearch(uint32_t eip, int* l, int *r, uint8_t type);
static void grade_backtrace1(int arg1);
static void grade_backtrace2(int arg1, int arg2);

void grade_backtrace(){
    grade_backtrace1(0x1111);
}

static void grade_backtrace1(int arg1){
    grade_backtrace2(0x2222, 0x1111);
}

static void grade_backtrace2(int arg1, int arg2){
    unsigned int ebp = read_ebp();
    unsigned int eip, stack_arg1, stack_arg2;

    while (1){
        if (ebp == 0){
            break;
        }
        int* ebp_ptr = (int *)ebp;
        eip = *(ebp_ptr + 1);
        stack_arg1 = *(ebp_ptr + 2);
        stack_arg2 = *(ebp_ptr + 3);

        int l = 0, r = (stab_end - stabs) - 1;
        stab_bsearch(eip, &l, &r, N_FUN);
        char* name;
        if(l==0){
            name = "<Unknow, beacuse in asm>";
        }else{
            name = stabs[l].n_strx + stabstr;
        }
        printf("caller name:%s\n%p:\t|%x|\n\teip:\t|%x|\n\targ1:\t|%x|^\n\targ2:\t|%x|^\n", name, ebp_ptr, *ebp_ptr, eip, stack_arg2, stack_arg1);
        ebp = *ebp_ptr;
    }
}

struct stab * stab_bsearch(uint32_t eip,int* region_l, int* region_r, uint8_t type){
    stabs = __STAB_BEGIN__;
    stab_end = __STAB_END__;
    int l = *region_l, r = *region_r;
    while(l < r){
        int true_m = (l+r)/2, m = true_m;

        //find the frist match type
        while(m>=l && (stabs[m].n_type != type || stabs[m].n_strx == 0)){
            m--;
        }

        /*printf("%d :: %d .. %d .. %d\n", l, r, true_m, m);*/
        //if m < l , that mean not in [l-m]
        if(m<l){
            l = true_m + 1;
            continue;
        }

        //find it
        int address = stabs[m].n_value;
        /*printf("add:%p eip:%p m_str:%x\n", address, eip, stabs[m].n_strx);*/
        if(address > eip){
            *region_r = m - 1;
            r = true_m - 1;
        }
        else if (address <= eip){
            *region_l = m;
            l = true_m + 1;
        }
    }
}

void print_stab(){
    stabs = __STAB_BEGIN__;
    stab_end = __STAB_END__;
    uint32_t i = 0;
    while (1){
        if (stabs + i >= stab_end){
            break;
        }
        int type = stabs[i].n_type;
        //函数地址
        if (type == N_SO || type == N_SOL || type == N_FUN || type == N_SLINE){
            if (stabs[i].n_strx != 0){
                printf("[%d] location: %p type: %x name:%s \n",i, stabs[i].n_value, type, stabstr + stabs[i].n_strx);
            }
            i++;
        }
        else {
            i++;
            continue;
        }
    }
}
