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