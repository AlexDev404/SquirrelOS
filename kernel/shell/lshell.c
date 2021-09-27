#include "lshell.h"
#include "cpu/cpuid/cpuid.h"
#include "kernel/apps/apps.h"

// VGA COLOR [ MOVED - DECLARED IN SCREEN.H]

/*
enum vga_color
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15,
};
*/

// FUNCTION PROTOTYPES
char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_execute(char **args);
int lsh_ls(char **args);
int lsh_echo(char **args);
int lsh_clear(char **args);
int about(char **args);
int run(char **args);
int lsh_man(char **args);
char *prompt = "LSH> ";
char os_name[] = "SquirrelOS";

/*
  Function Declarations for builtin shell commands:
 */
int lsh_help(char **args);
int lsh_exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
    "help",
    "exit",
    "ls",
    "echo",
    "clear",
    "about",
    "run",
    "man"};

int (*builtin_func[])(char **) = {
    &lsh_help,
    &lsh_exit,
    &lsh_ls,
    &lsh_echo,
    &lsh_clear,
    &about,
    &run,
    &lsh_man};

int lsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/

int lsh_man(char **args)
{
    return appLaunch(args, true);
}

int run(char **args)
{
    // DIRECT = ARGS[1] == NULL
    // NO-DIRECT = ARGS[1] == TRUE
    
    if (strcmp(args[0], "run") && args[1] == NULL) // EXAMPLE: run (use arg0, direct = true)
    {
        print_string("\nEnter App to Run: ");
        string app = lsh_read_line();
        int appCode = appLaunch(args, true);
        if (appCode == 2)
        {
            printf("\nApp Not Found\nAvailable Applications Include:\n");
            for (int i = 0; i < num_builtin_apps(); i++)
            {
                printf("  %s\n", builtin_apps[i]);
            }
        }
    }
    else if (strcmp(args[0], "run") && strcmp(args[1], "--help")) // EXAMPLE: run --help (use arg0, direct = true)
    {
        int i;
        printf("App Runner for %s\n", os_name);
        printf("Type program names and arguments, and hit enter.\n");
        printf("The following are included:\n");

        for (i = 0; i < num_builtin_apps(); i++)
        {
            printf("  %s\n", builtin_apps[i]);
        }

        printf("Use the man command for information on other programs.\n");
        return 1;
    }
    else if (args[1] == NULL) // EXAMPLE: textedit (use arg1, direct = true)
    {
        // Launch an app from the apps directory
        int appCode = appLaunch(args, true);
        if (appCode == 2)
        {
            printf("lsh: %s: command not found\n", args[0]);
        }
    }

    else if (args[1] != NULL && strcmp(args[0], "run")) // EXAMPLE: run textedit (use arg1, direct = false)
    {
        // Launch an app from the apps directory
        int appCode = appLaunch(args, false);
        if (appCode == 2)
        {
            printf("lsh: %s: %s: application not found\n", args[0], args[1]);
        }
    }

    // BELOW CODE HAS AN ERROR SOMEWHERE

    else if (args[1] != NULL) // EXAMPLE: ccowsay --list (use arg1, direct = true)
    {
        // Launch an app from the apps directory
        int appCode = appLaunch(args, true);
        if (appCode == 2)
        {
            printf("STDERR: Application Exited With Return Code 2\n");
        }
    }
}

int about(char **args)
{
    printf("%s v0.0.1", os_name);
    print_string("\nBy Immanuel Garcia\n");
    return 1;
}

int lsh_clear(char **args)
{
    clearScreen();
    init_vga(GREEN, BLACK);
}

int lsh_echo(char **args)
{
    // set the initial position to the size of the args we have

    int position = sizeof(args);

    // Check if args is greater than one, if it is, we'll subtract one from the position to avoid any garbage from being collected + displayed

    // Check if we were fooled into printing out our name

    if (args[1] == "\0")
    {
        printf("\n");
        return 1;
    }

    // IMPLEMENTATION OF ECHO OFF AND ECHO ON COMMANDS

    if (strcmp(args[1], "off"))
    {
        printf("ECHO is OFF");
        prompt = "";
    }

    if (strcmp(args[1], "on"))
    {
        printf("ECHO is ON");
        prompt = "LSH> ";
    }

    // Loop through all the args that were typed

    if (!strcmp(args[1], "on") && !strcmp(args[1], "off"))
    {
        for (int i = 1; args[i] != "\0"; i++)
        {
            // Spit back what the user typed back onto the screen
            printf("%s ", args[i]);
        }
    }

    // Print a new line after execution to make way for the terminal

    printf("\n");
    return 1;
}

int lsh_ls(char **args)
{
    char *name;
    for (int i = 0; i < file_count(); ++i)
    {
        name = file_get_name(i);
        if (name != FILE_NOT_FOUND)
        {
            print_string(name);
            int size = file_size(name);
            print_string("\t");
            print_int(size);
            print_string("\n");
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    int i;
    printf("Stephen Brennan's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < lsh_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args)
{
    printf("Executing This Command Will Power Off The System.\nAre you sure you want to do carry forth with this? (y / n) ");
    string ch = lsh_read_line();

    if (strcmp(ch, "y"))
    {
        printf("\nPowering off...\n");
        acpiPowerOff();
        return 0;
    }

    else if (strcmp(ch, "n"))
    {
        printf("\nSystem shutoff cancelled.\n");
        return 1;
    }
    else
    {
        printf("\nInvalid Choice (%s)! Try again!\n", ch);
        return 1;
    }
}

/*
 *
 * ****************
 * MAIN SHELL LOOP
 * ****************
 * 
 */

void lsh_loop()
{
    char *line;
    char **args;
    int status;

    // print_string("TEST");
    // print_string_colored("TEST\n", GREEN, BLACK);
    do
    {
        printf(prompt);
        line = lsh_read_line();
        // print_string("\nLINE: \n");
        // printf(line);
        //  print_string("\n");
        args = lsh_split_line(line);
        // print_string("\nTOKEN: \n");
        // printf(args);
        // print_string("\n");
        status = lsh_execute(args);

        kfree(line);
        kfree(args);
    } while (status);
}

////////////////////////////////////

// READLINE IMPLEMENTATION

///////////////////////////////////

#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE + 1;
    char *buffer = calloc(bufsize, sizeof(char));
    string c;

    if (!buffer)
    {
        print_string("lsh: allocation error\n");
        panic("MEM_ERR");
    }

    while (true)
    {
        // Read a character
        // If set to false, backspace breaks for some reason...

        c = readStrShell(true, buffer);
        //char *strcat(c, returnValue);

        // THIS CODE RUNS AFTER A CARRIAGE RETURN

        // print_string("\n");
        // print_int(strlen(buffer));
        // print_string("\n");
        // printf(buffer);
        print_string("\n");
        //   printf("%s\n", buffer);
        return buffer;

        // If we have exceeded the buffer, reallocate.
        if (sizeof(buffer) >= bufsize)
        {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, malloc(sizeof(char) * bufsize), bufsize * 2);
            if (!buffer)
            {
                print_string("lsh: readline: allocation error\n");
                panic("MEM_ERR");
            }
        }
    }
}

// TOKENIZER

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line)
{

    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = calloc(bufsize, sizeof(char *));
    char *token;

    if (!tokens)
    {
        print_string("lsh: allocation error\n");
        panic("EXIT_FAILURE");
    }

    /*
    // ZERO OUT TOKENS ARRAY

    for (int i = 0; i < strlen(tokens); i++)
    {
        tokens[i] = "\0";
    }
*/
    // printf("RECIEVED STRING: %s\n", line);

    token = strtok(line, LSH_TOK_DELIM);

    while (token != NULL)
    {
        // printf("CURRENT TOKEN = %s\n", token);
        // printf("INSERTING TOKEN (%s) AT POSITION %d\n", token, position);

        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, malloc(sizeof(char) * bufsize), bufsize * 2);
            if (!tokens)
            {
                print_string("lsh: tokenizer: allocation error\n");
                panic("EXIT_FAILURE");
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    // Append ending to args

    tokens[strlen(tokens)] = "\0";

    /* 

    printf("TOKENS: ");
    if (position > 1)
    {
        position = position - 1;
    }

    for (int i = 0; i < position; i++)
    {
        printf("%s, ", tokens[i]);
    }
*/

    return tokens;
    ////////////////////////
    // STRTOK TESTING    //
    //////////////////////

    /*

char str[] = "this, is the string - I want to parse";
char delim[] = " ,-";
char* token;

for (token = strtok(str, delim); token; token = strtok(NULL, delim))
{
    printf("token=%s\n", token);
}

*/
}

// LSH EXECUTE IMPLEMENTATION

int lsh_execute(char **args)
{
    int i;

    // printf(args[0]);

    if (args[0] == "\0")
    {
        // An empty command was entered.
        return 1;
    }

    for (i = 0; i < lsh_num_builtins(); i++)
    {
        /*   if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }*/
        if (strcmp(args[0], builtin_str[i]))
        {
            return (*builtin_func[i])(args);
        }
    }

    return run(args);
    /// ELSE return;
}
