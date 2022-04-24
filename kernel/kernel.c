/*
 * Copyright 2021 Harvey Xing
 * Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
 * Improved upon by Immanuel Garcia
 */

#include "drivers/screen/screen.h" // Screen doesn't work with FB
#include "drivers/keyboard/keyboard.h"
#include "shell/lshell.h"
#include "kernel/multiboot2.h"
#include "include/printf.h"
#include "include/types/types.h"
#include "panic.h"

void kmain(struct multiboot *mboot_ptr)
{


	init_vga(LIGHT_GREY, BLACK); // INIT VGA LIGHT_GREY ON BLACK
	clearScreen();
	printf("Welcome to SquirrelOS!\nPlease enter a command\n");
	printf("Enter 'help' for commands\n\n\n");
	// printf("TEST> ");
	// scanf(true);
	lsh_loop();
	panic("EXITED KERNEL");
}
