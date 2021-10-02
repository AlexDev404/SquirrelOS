/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
Improved upon by Immanuel Garcia
*/

#include "serialapp.h"
#include "../apps.h"
#include "drivers/serial/serial.h"

void serialapp()
{
    clearScreen();
    printf("Available Commands\nwrite: write byte to serial port\nread: read byte from serial port\nenter 'quit' to quit");
    promptSerial();
    printf("\n");
    return 1;
}
void promptSerial()
{
    print_string("\nSerial> ");
    char *buffer = calloc(2 * 2048, sizeof(char));
    string cmd = readStrShell(true, buffer);

    if (strcmp(buffer, "write"))
    {
        print_string("\nchar to write: ");
        char ch = readStr();
        write_serial(ch);
    }
    else if (strcmp(buffer, "read"))
    {
        string reading = read_serial();
        print_string("\n");
        print_string("Reading: ");
        print_string(reading);
        print_string("\n");
    }
    else if (strcmp(buffer, "quit"))
    {

        clearScreen();
        return 1;
    }
    else if (buffer == "")
    {
        promptSerial();
    }
    else
    {
        printf("\nSerialApp: Unknown Command: %s\n", buffer);
        promptSerial();
    }
}