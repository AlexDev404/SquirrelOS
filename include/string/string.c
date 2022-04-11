#include "string.h"


uint32 strlen(const char *str)
{
  uint32 length = 0;
  while (str[length])
    length++;
  return length;
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


char *concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
  // in real code you would check for errors in malloc here
  strcpy(result, s1);
  strcat(result, s2);
  return result;
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

void append(char s[], char n)
{
  int len = strlen(s);
  s[len] = n;
  s[len + 1] = '\0';
}