#include "apps.h"

int appLaunch(char **args, bool direct)
{
    for (int i = 0; i < num_builtin_apps(); i++)
    {
        /*   if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }*/
        if (direct)
        {
            if (strcmp(args[0], builtin_apps[i]))
            {
                // printf("Passing the following args to the application:\n"); // DEBUG

                // Hopefully this helps
                // Retokenize the arguments

                //  args[strlen(args)] = "\0";
                /*
 * DEBUG
                for (int i = 0; args[i] != "\0"; i++)
                {
                    printf("%s, ", args[i]);
                }

                */
                return (*builtin_appFunc[i])(args);
            }
        }

        if (!direct)
        {
            if (strcmp(args[1], builtin_apps[i]))
            {
                return (*builtin_appFunc[i])(args);
            }
        }
    }
    return 2;
}