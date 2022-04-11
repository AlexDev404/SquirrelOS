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


int assert(int expr)
{
    if (expr)          
  {                  
    return 0;        
  }                  
  else {
    aFailed(F_NUM, __LINE__);
  }
}