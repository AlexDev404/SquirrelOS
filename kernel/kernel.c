/*
 * Copyright 2021 Harvey Xing
 * Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
 * Improved upon by Immanuel Garcia
 */

#include "drivers/screen/screen.h"
#include "drivers/keyboard/keyboard.h"
#include "shell/lshell.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "fs/vfs.h"
#include "fs/initrd/initrd.h"
#include "kernel/multiboot.h"
#include "drivers/serial/serial.h"
#include "drivers/pci/pci.h"
#include "drivers/mouse/mouse.h"
#include "fs/fs.h"
#include "drivers/acpi/acpi.h"
#include "fs/tar.h"
#include "include/printf.h"
#include "fonts/font.h"
#include "drivers/timer/timer.h"

void kernel_entry(struct multiboot *mboot_ptr)
{
	uint32 initrd_location = *((uint32 *)mboot_ptr->mods_addr);
	init_vga(LIGHT_GREY, BLACK); // INIT VGA LIGHT_GREY ON BLACK
	init_gdt();
	printf("GDT Initialised\n");
	beep();
	init_idt();
	printf("IDT Initialised\n");
	serial_init();
	printf("Serial Driver Initialised\n");
	pci_init();
	printf("PCI Driver Initialised\n");
	init_acpi();
	printf("Initialised ACPI\n");
	fs_root = initialise_initrd(initrd_location);
	if (!fs_root)
	{
		panic("RAMDISK error");
	}
	else
	{
		printf("Loaded Initial RAMDISK\n");
	}
	int tarfound = parse(initrd_location);
	printf("\nFiles Found in RAMDISK: ");
	print_int(tarfound);
	printf("\n");
	fsinit();
	printf("Initialised the Filesystem\n");
	mouse_init();
	printf("Initialised Mouse Driver\n");
	clearScreen();
	printf("\nWelcome to SquirrelOS!\nPlease enter a command\n");
	printf("Enter 'help' for commands\n\n\n");
	lsh_loop();
	panic("EXITED KERNEL");

}
