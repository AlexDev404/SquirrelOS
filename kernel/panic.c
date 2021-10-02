/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#include "panic.h"
#include "apps/apps.h"

char *panic_title = "KERNEL PANIC";
char *panic_body = "SYSTEM HALTING!";
int panic_color_bg = 0x4F;
int panic_color_fg = 0xF4;

void panic(char *str)
{
	asm volatile("cli");
	panic_xander(str);
	asm volatile("hlt");
}

int panic_xander(char *text)
{
	sw_color(panic_color_bg);
	clearScreen();
	sw_color(panic_color_fg);
	centerText(panic_title);
	// TOP
	move_cursor(0, 10);
	sw_color(panic_color_bg); // 0xbg,fg
	centerText(panic_body);
	move_cursor(0, 11);
	centerText(text);
}

/*
 * EXPECTED RESULT
 * -------------KERNEL PANIC!-------------------
 * 
 *              SYSTEM HALTING!
 * 
 */