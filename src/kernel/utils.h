/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include "drivers/screen/screen.h"
#include "panic.h"


typedef struct __attribute__((packed)) {
    uint16 size : 12;
    uint8 flags : 4;
} mem_header_t;


char memory[20000];

struct block{
 size_t size; /*Carries the size of the block described by it*/
 int free;  /*This flag is used to know whether the block described by the metadata structure is free or not -- > if free, it is set to 1. Otherwise 0.*/
 struct block *next; /*Points to the next metadata block*/
};
struct block *freeList=(void*)memory;

// void initialize();
// void split(struct block *fitting_slot,size_t size);
// void *MyMalloc(size_t noOfBytes);



#define KERNEL_MEMORY_OFFSET_START 0xffffff
#define KERNEL_MEMORY_OFFSET_END	0xffffffff
#define MEMORY_EMPTY 0x0
#define MEMORY_INDEX_BASE_SIZE 10000

uint32 strlen(const char* str);
uint32 digit_count(int num);
void itoa(int num, char *number);
void* malloc(uint32 size);
void memset(uint8 *dest, uint8 val, uint32 len);
void memcpy(char *source, char *dest, int nbytes);
string int_to_string(int n);
int str_to_int(string ch);
void int_to_ascii(int n, char str[]);
uint8 strcmp(string ch1,string ch2);
int memcmp(void *s1, void *s2, int len);
int rand(int RAND_MAX);
void srand(unsigned int seed);
string strchr(const char* str, int c);
char * strcpy (char *dest, const char *src);
char * strncpy(char* dest, const char *src, size_t n);
#define my_sizeof(type) (char *)(&type+1)-(char*)(&type)
uint32 kmalloc(uint32 size, int align, uint32 *phys_addr);
void page();
void merge();
void kfree(void* ptr);
uint32 memlen(char *s);
char* strcat(char* destination, const char* source);
void bzero(void *b, size_t len);
char *concat(const char *s1, const char *s2);
bool isspace(string c);
void *realloc(void *ptr, size_t originalLength, size_t newLength);
void aFailed(char *file, int line);
#define assert(expr);
#endif