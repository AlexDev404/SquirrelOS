#include "man.h"
#include "../apps.h"

int man(char **args)
{
    int i;
    printf("NOT IMPLEMENTED\n");

    // Looks like I'll have to put this in every application * sigh *
    args[strlen(args)] = "\0";

    for (int i = 0; args[i] != "\0"; i++)
    {
        printf("%s, ", args[i]);
    }
    return 1;
}