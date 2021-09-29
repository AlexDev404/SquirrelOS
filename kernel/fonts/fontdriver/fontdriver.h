#ifndef FONTDRIVER_H
#define FONTDRIVER_H

#define PSF_FONT_MAGIC 0x864ab572


#include "drivers/screen/screen.h"
#include "fs/fs.h"
#include "include/types/types.h"
#include "include/math/math.h"
#include "drivers/keyboard/keyboard.h"
#include "include/utils.h"
#include "include/limits.h"

 
typedef struct {
    uint32 magic;         /* magic bytes to identify PSF */
    uint32 version;       /* zero */
    uint32 headersize;    /* offset of bitmaps in file, 32 */
    uint32 flags;         /* 0 if there's no unicode table */
    uint32 numglyph;      /* number of glyphs */
    uint32 bytesperglyph; /* size of each glyph */
    uint32 height;        /* height in pixels */
    uint32 width;         /* width in pixels */
} PSF_font;

void psf_init();
void putchar(unsigned short int c, int cx, int cy, uint32 fg, uint32 bg);

#endif