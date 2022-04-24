/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#include "utils.h"

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


unsigned long next = 1;

extern uint32 _timestamp_edx();
extern uint32 _timestamp_eax();


int rand(int RAND_MAX, int seed) {
   int next;
   if(!RAND_MAX){
      RAND_MAX = 999;
   }
   if (!seed) {
      next = floor(475475744 / 1000); // seed / 1000 --> TODO: use getDate to be used as seed
   } else {
      next = seed;
   }
   next = next * 1103515245 + 12345;
   return ((unsigned int)(next / 65536) % RAND_MAX) + 1;
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

