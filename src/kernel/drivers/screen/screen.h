/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#ifndef SCREEN_H
#define SCREEN_H

#include "../../types.h"
#include "../../utils.h"
#include "../ports/ports.h"

#define VGA_ADDRESS 0xb8000
#define BUFSIZE 2200

uint16 *vga_buffer;

#define NULL 0

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

#define BOX_MAX_WIDTH 78
#define BOX_MAX_HEIGHT 23

#define BOX_SINGLELINE 1
#define BOX_DOUBLELINE 2

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color);
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color);
void init_vga(uint8 fore_color, uint8 back_color);
void print_new_line();
void scroll_up();
void print_char(char ch);
void print_string(char *str);
void print_int(int num);
void clearScreen();
void print_string_colored(char *str, uint8 fore_color, uint8 back_color);
void print_binary(uint32 num);

#endif