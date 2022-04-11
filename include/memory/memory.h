#ifndef MEMORY_H
#define MEMORY_H
#include "../types/types.h"
#include "../assert/assert.h"

#define KERNEL_MEMORY_OFFSET_START 0xffffff
#define KERNEL_MEMORY_OFFSET_END	0xffffffff
#define MEMORY_EMPTY 0x0
#define MEMORY_INDEX_BASE_SIZE 10000
uint8 *memory_index[MEMORY_INDEX_BASE_SIZE];
uint32 free_mem_addr = 0x10000;
char memory[10000];


typedef struct __attribute__((packed)) {
    uint16 size : 12;
    uint8 flags : 4;
} mem_header_t;

struct block{
 size_t size; /*Carries the size of the block described by it*/
 int free;  /*This flag is used to know whether the block described by the metadata structure is free or not -- > if free, it is set to 1. Otherwise 0.*/
 struct block *next; /*Points to the next metadata block*/
};
struct block *freeList=(void*)memory;


void* malloc(uint32 size);
void memset(uint8 *dest, uint8 val, uint32 len);
void memcpy(char *source, char *dest, int nbytes);
int memcmp(void *s1, void *s2, int len);
uint32 kmalloc(uint32 size, int align, uint32 *phys_addr);
void kfree(void* ptr);
uint32 memlen(char *s);
void bzero(void *b, size_t len);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t originalLength, size_t newLength);

void page();

#endif