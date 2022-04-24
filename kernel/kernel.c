/*
 * Copyright 2021 Harvey Xing
 * Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
 * Improved upon by Immanuel Garcia
 */

#include "drivers/keyboard/keyboard.h"
#include "kernel/multiboot2.h"
#include "include/types/types.h"

typedef struct
{
	uintptr_t address;
	uint32_t pitch;
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
} fb_t;

static fb_t fb;

/* "fb" stands for "framebuffer" throughout the code.
 */
void init_fb(mb2_t *boot)
{
	mb2_tag_fb_t *fb_info = (mb2_tag_fb_t *)mb2_find_tag(boot, MB2_TAG_FB);

	// Mappings
	fb.width = fb_info->width;
	fb.height = fb_info->height;
	fb.pitch = fb_info->pitch;
	fb.bpp = fb_info->bpp;

	/*
		if (fb.bpp != 32) {
			printke("unsupported bit depth: %d", fb.bpp);
		}
	*/
	uintptr_t address = (uintptr_t)fb_info->addr;
	fb.address = address;
}

uint32_t *get_pixel(x, y)
{
	return (uint32_t *)(fb.address + y * fb.pitch + x * fb.bpp / 8); // VESA???
}

void putpixel(int pos_x, int pos_y, int VGA_COLOR)
{
    *get_pixel(pos_x, pos_y) = VGA_COLOR;
	
}

void kmain(struct multiboot *mboot_ptr)
{

	// Keyboard buffer
	string buffstr = (string)malloc(200);
	memset(buffstr, 0, strlen(buffstr));
	// Initialize framebuffer
	init_fb(mboot_ptr);
	putpixel(100, 100, 4);
	/*
	printf("%lf\n", lfsr113());
    printf("%lf\n", lfsr113());
    printf("%lf\n", lfsr113());
    printf("%lf\n", lfsr113());
	*/
}
