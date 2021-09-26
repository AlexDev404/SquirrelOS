/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#include "utils.h"

uint32 strlen(const char *str)
{
  uint32 length = 0;
  while (str[length])
    length++;
  return length;
}

uint32 digit_count(int num)
{
  uint32 count = 0;
  if (num == 0)
    return 1;
  while (num > 0)
  {
    count++;
    num = num / 10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if (num == 0 && dgcount == 1)
  {
    number[0] = '0';
    number[1] = '\0';
  }
  else
  {
    while (num != 0)
    {
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

uint8 *memory_index[MEMORY_INDEX_BASE_SIZE];

void *malloc(uint32 size)
{
  uint32 i = 0;
  while (true)
  {
    // search
    while (memory_index[i] != MEMORY_EMPTY)
    {
      i += 2;
    }
    uint8 *last_page_end = memory_index[i - 1];
    uint32 next_page_start_id = i;
    while (memory_index[next_page_start_id] == MEMORY_EMPTY)
    {
      ++next_page_start_id;
    }
    // verify
    if (memory_index[next_page_start_id] - last_page_end > size)
    {
      if (i >= MEMORY_INDEX_BASE_SIZE)
      {
        panic("");
      }
      if (size + last_page_end + 1 >= KERNEL_MEMORY_OFFSET_END)
      {
        panic();
      }
      // allocate
      memory_index[i] = last_page_end + 1;
      memory_index[i + 1] = memory_index[i] + size;
      return (void *)memory_index[i];
    }
  }
}

void memset(uint8 *dest, uint8 val, uint32 len)
{
  uint8 *temp = (uint8 *)dest;
  for (; len != 0; len--)
    *temp++ = val;
}

void memcpy(char *source, char *dest, int nuint8s)
{
  int i;
  for (i = 0; i < nuint8s; i++)
  {
    *(dest + i) = *(source + i);
  }
}

void int_to_ascii(int n, char str[])
{
  int i, sign;
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do
  {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    str[i++] = '-';
  str[i] = '\0';

  /* TODO: implement "reverse" */
  return str;
}

string int_to_string(int n)
{
  string ch = malloc(50);
  int_to_ascii(n, ch);
  int len = strlen(ch);
  int i = 0;
  int j = len - 1;
  while (i < (len / 2 + len % 2))
  {
    char tmp = ch[i];
    ch[i] = ch[j];
    ch[j] = tmp;
    i++;
    j--;
  }
  return ch;
}

int str_to_int(string ch)
{
  int n = 0;
  int p = 1;
  int strlength = strlen(ch);
  int i;
  for (i = strlength - 1; i >= 0; i--)
  {
    n += ((int)(ch[i] - '0')) * p;
    p *= 10;
  }
  return n;
}

uint8 strcmp(string ch1, string ch2)
{
  uint8 result = 1;
  uint8 size = strlen(ch1);
  if (size != strlen(ch2))
    result = 0;
  else
  {
    uint8 i = 0;
    for (i; i <= size; i++)
    {
      if (ch1[i] != ch2[i])
        result = 0;
    }
  }
  return result;
}

int memcmp(void *s1, void *s2, int len)
{
  uint8 *p = s1;
  uint8 *q = s2;
  int charCompareStatus = 0;
  //If both pointer pointing same memory block
  if (s1 == s2)
  {
    return charCompareStatus;
  }
  while (len > 0)
  {
    if (*p != *q)
    {
      //compare the mismatching character
      charCompareStatus = (*p > *q) ? 1 : -1;
      break;
    }
    len--;
    p++;
    q++;
  }
  return charCompareStatus;
}

unsigned long next = 1;

extern uint32 _timestamp_edx();
extern uint32 _timestamp_eax();

int rand(int RAND_MAX)
{
  next = next * 1103515245 + 12345;
  return (unsigned int)(next / 65536) % RAND_MAX + 1;
}

void srand(unsigned int seed)
{
  next = seed;
}

string strchr(const char *str, int c)
{
  while (*str != c)
  {
    if (*str == '\0')
    {
      return NULL;
    }
    str++;
  }

  return (char *)str;
}

char *strcpy(char *dest, const char *src)
{
  do
  {
    *dest++ = *src++;
  } while (*src != 0);
}

char *strncpy(char *dest, const char *src, size_t n)
{
  size_t i = 0;
  for (; i < n && src[i]; i++)
  {
    dest[i] = src[i];
  }

  if (i < n)
    dest[i] = 0;

  return dest;
}

uint32 free_mem_addr = 0x10000;

uint32 kmalloc(uint32 size, int align, uint32 *phys_addr)
{

  if (align == 1 && (free_mem_addr & 0xFFFFF000))
  {
    free_mem_addr &= 0xFFFFF000;
    free_mem_addr += 0x1000;
  }

  if (phys_addr)
    *phys_addr = free_mem_addr;

  uint32 ret = free_mem_addr;
  free_mem_addr += size;
  return ret;
}

void append(char s[], char n)
{
  int len = strlen(s);
  s[len] = n;
  s[len + 1] = '\0';
}

void hex_to_ascii(int n, char str[])
{
  append(str, '0');
  append(str, 'x');
  char zeros = 0;

  int32 tmp;
  int i;
  for (i = 28; i > 0; i -= 4)
  {
    tmp = (n >> i) & 0xF;
    if (tmp == 0 && zeros == 0)
      continue;
    zeros = 1;
    if (tmp > 0xA)
      append(str, tmp - 0xA + 'a');
    else
      append(str, tmp + '0');
  }

  tmp = n & 0xF;
  if (tmp >= 0xA)
    append(str, tmp - 0xA + 'a');
  else
    append(str, tmp + '0');
}

void page()
{
  uint32 phys_addr;
  uint32 page = kmalloc(1000, 1, &phys_addr);
  char page_str[16] = "";
  hex_to_ascii(page, page_str);
  char phys_str[16] = "";
  hex_to_ascii(phys_addr, phys_str);
  print_string("Page: ");
  print_string(page_str);
  print_string(", physical address: ");
  print_string(phys_str);
  print_string("\n");
}

void kfree(void *ptr)
{
  mem_header_t *header = (mem_header_t *)(ptr - sizeof(mem_header_t));
  header->flags |= 1;
}

uint32 memlen(char *s)
{ // Just strlen() with a different name lol
  uint32 i = 0;
  while (s[i++])
    ;
  return i;
}

char *strcat(char *destination, const char *source)
{
  // make `ptr` point to the end of the destination string
  char *ptr = destination + strlen(destination);

  // appends characters of the source to the destination string
  while (*source != '\0')
  {
    *ptr++ = *source++;
  }

  // null terminate destination string
  *ptr = '\0';

  // the destination is returned by standard `strcat()`
  return destination;
}

void bzero(void *b, size_t len)
{

  (void)memset(b, 0, len);
}

void *calloc(size_t nmemb, size_t size)
{
  char *p;

  // If either is zero just return NULL.
  if (nmemb == 0 || size == 0)
  {
    return NULL;
  }

  // Malloc the area and zero it out.
  else
  {
    p = malloc(nmemb * size);
    bzero(p, nmemb * size);
    return p;
  }
}

char *concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
  // in real code you would check for errors in malloc here
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

bool isspace(string c)
{
  int i;
  int len = 0;
  for (i = 0; i < strlen(c); i++)
  {
    switch (c[i])
    {
    case '\0':
      len++;
      break;
    case '\t':
      len++;
      break;
    case ' ':
      len++;
      break;
    default:
      return false;
    }
  }
  if (len == strlen(c))
  {
    return true;
  }
}

bool isbreak(string c)
{
  int i;
  for (i = 0; i < strlen(c); i++)
  {
    switch (c[i])
    {
    case '\n':
      return true;
    case '\r':
      return true;
    default:
      return false;
    }
  }
}

// ASSERT IMPLEMENATION

#define F_NUM 1

void aFailed(char *file, int line)
{
  print_string("ASSERTATION FAILED!\n");
  print_string("-->");
  print_string(file);
  print_string(", ");
  print_int(line);
};

#define assert(expr) \
  if (expr)          \
  {                  \
    return 0;        \
  }                  \
  else               \
    aFailed(F_NUM, __LINE__);

// This function is similar to realloc() and implements the same semantics,
// except that the caller must explicitly pass the original size of the
// memory block pointed to by 'ptr', as well as the desired size.
void *realloc(void *ptr, size_t originalLength, size_t newLength)
{
  // Note that because we cannot rely on implementation details of the standard library,
  // we can never grow a block in place like realloc() can. However, it is semantically
  // equivalent to allocate a new block of the appropriate size, copy the original data
  // into it, and return a pointer to that new block. In fact, realloc() is allowed to
  // do this, as well. So we lose a possible performance optimization (that is rarely
  // possible in practice anyway), but correctness is still ensured, and the caller
  // never need be the wiser.
  //
  // Likewise, we cannot actually shrink a block of memory in-place, so we either
  // have to return the block unchanged (which is legal, because a block of memory
  // is always allowed to be *larger* than necessary), or allocate a new smaller
  // block, copy the portion of the original data that will fit, and return a
  // pointer to this new shrunken block. The latter would actually be slower,
  // so we'll avoid doing this extra work when possible in the current implementation.
  // (You might need to change this if memory pressure gets out of control.)

  if (newLength == 0)
  {
    kfree(ptr);
    return NULL;
  }
  else if (!ptr)
  {
    return malloc(newLength);
  }
  else if (newLength <= originalLength)
  {
    return ptr;
  }
  else
  {
    assert((ptr) && (newLength > originalLength));
    void *ptrNew = malloc(newLength);
    if (ptrNew)
    {
      memcpy(ptrNew, ptr, originalLength);
      kfree(ptr);
    }
    return ptrNew;
  }
}
/*

// STRTOK IMPLEMENTATION: https://stackoverflow.com/a/28949236/10976415

char* strtok(char* s, char* delm)
{
    static int currIndex = 0;
    if(!s || !delm || s[currIndex] == '\0')
    return NULL;
    char *W = (char *)malloc(sizeof(char)*100);
    int i = currIndex, k = 0, j = 0;

    while (s[i] != '\0'){
        j = 0;
        while (delm[j] != '\0'){
            if (s[i] != delm[j])
                W[k] = s[i];
            else goto It;
            j++;
        }

        i++;
        k++;
    }
It:
    W[i] = 0;
    currIndex = i+1;
    //Iterator = ++ptr;
    return W;
}
*/
///////////////////////////////////////////////////

#define DICT_LEN 256

int *create_delim_dict(char *delim)
{
  int *d = (int *)malloc(sizeof(int) * DICT_LEN);
  memset((void *)d, 0, sizeof(int) * DICT_LEN);

  int i;
  for (i = 0; i < strlen(delim); i++)
  {
    d[delim[i]] = 1;
  }
  return d;
}

char *strtok(char *str, char *delim)
{

  static char *last, *to_free;
  int *deli_dict = create_delim_dict(delim);

  if (!deli_dict)
  {
    /*this check if we allocate and fail the second time with entering this function */
    if (to_free)
    {
      kfree(to_free);
      to_free = NULL;
    }
    return NULL;
  }

  if (!deli_dict)
  {

    return NULL;
  }

  if (str)
  {
    last = (char *)malloc(strlen(str) + 1);
    if (!last)
    {
      kfree(deli_dict);
      deli_dict = NULL;
      return NULL;
    }
    to_free = last;
    strcpy(last, str);
  }

  while (deli_dict[*last] && *last != '\0')
  {
    last++;
  }
  str = last;
  if (*last == '\0')
  {
    kfree(deli_dict);
    deli_dict = NULL;
    kfree(to_free);
    to_free = NULL;
    return NULL;
  }
  while (*last != '\0' && !deli_dict[*last])
  {
    last++;
  }

  *last = '\0';
  last++;
  if (deli_dict)
  {
    kfree(deli_dict);
    deli_dict = NULL;
  }
  return str;
}

//////////////////////////////////////////////////

void removeChar(char *str, char garbage)
{

  char *src, *dst;
  for (src = dst = str; *src != '\0'; src++)
  {
    *dst = *src;
    if (*dst != garbage)
      dst++;
  }
  *dst = '\0';
}

// IS ALPHANUM (USED FOR FILTERING OUT KEYBOARD INPUT)

int isalnum(int c)
{
  char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890., "
                    "abcdefghijklmnopqrstuvwxyz1234567890., ";
  char *letter = alphabet;

  while (*letter != '\0' && *letter != c)
    ++letter;

  if (*letter)
    return 1;

  return 0;
}