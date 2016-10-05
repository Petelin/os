#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_
#include "types.h"

void grade_backtrace();

void print_stab();

char * stab_name_from_eip(uint32_t eip);

#endif

