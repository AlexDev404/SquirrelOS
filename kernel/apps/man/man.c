#include "man.h"
#include "../apps.h"

int man(char **args)
{
    int i;
    printf("NOT IMPLEMENTED\n");
    for (i = 0; args[i] != "\0"; i++)
    {
        printf("%s, ", args[i]);
    }
    printf("%d", i);
    return 1;
}