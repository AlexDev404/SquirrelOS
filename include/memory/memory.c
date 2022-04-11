#include "memory.h"

void *malloc(uint32 size)
{
  uint32 i = 0;

  // search
  while (memory_index[i] != MEMORY_EMPTY)
  {
    i += 2;
  }
  // print_string("ALLOCATION STARTED.");
  uint8 *last_page_end = memory_index[i - 1];
  uint32 next_page_start_id = i;
  // int j = 0;
  //    clearScreen();
  while (memory_index[next_page_start_id] == MEMORY_EMPTY)
  {
    /*    if(j < 1){
        print_string("ALLOCATION IN PROGRESS...");
        }*/
    ++next_page_start_id;
    //    j++;
  }
  // verify
  //  print_string("VERIFY STARTED...");
  if (memory_index[next_page_start_id] - last_page_end > size)
  {
    if (i >= MEMORY_INDEX_BASE_SIZE)
    {
      panic("MALLOC: VERIFY_MEM: Index was greater than BASE_SIZE");
    }
    if (size + last_page_end + 1 >= KERNEL_MEMORY_OFFSET_END)
    {
      panic("MALLOC: VERIFY_MEM: SIZE was greater than KERNEL_OFFSET");
    }
  }
  // allocate
  memory_index[i] = last_page_end + 1;
  memory_index[i + 1] = memory_index[i] + size;
//  print_string("ALLOCATION FINISHED.");
  return (void *)memory_index[i];
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

int memcmp(void *s1, void *s2, int len)
{
  uint8 *p = s1;
  uint8 *q = s2;
  int charCompareStatus = 0;
  // If both pointer pointing same memory block
  if (s1 == s2)
  {
    return charCompareStatus;
  }
  while (len > 0)
  {
    if (*p != *q)
    {
      // compare the mismatching character
      charCompareStatus = (*p > *q) ? 1 : -1;
      break;
    }
    len--;
    p++;
    q++;
  }
  return charCompareStatus;
}

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