#ifndef STRING_H
#define STRING_H
#include "../types/types.h"
#include "../memory/memory.h"


uint32 strlen(const char *str);
uint8 strcmp(string ch1, string ch2);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strcat(char *destination, const char *source);
char *concat(const char *s1, const char *s2);
char *strtok(char *str, char *delim);
string strchr(const char *str, int c);
void append(char s[], char n);

#endif