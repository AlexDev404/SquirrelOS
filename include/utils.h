/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#ifndef UTILS_H
#define UTILS_H

#include "types/types.h"
#include "drivers/screen/screen.h"
#include "kernel/panic.h"
#include "assert/assert.h"
#include "memory/memory.h"
#include "drivers/rtc/rtc.h"

#define	EXIT_FAILURE	1
#define	EXIT_SUCCESS	0
#define	EXIT_CONTINUE	2


uint32 digit_count(int num);
void itoa(int num, char *number);
string int_to_string(int n);
int str_to_int(string ch);
void int_to_ascii(int n, char str[]);
int rand(int RAND_MAX, int seed);
void srand(unsigned int seed);
string strchr(const char* str, int c);
bool isspace(string c);

#endif
