#ifndef ASSERT_H
#define ASSERT_H
#include "../types/types.h"

void aFailed(char *file, int line);
int assert(int expr);

#endif