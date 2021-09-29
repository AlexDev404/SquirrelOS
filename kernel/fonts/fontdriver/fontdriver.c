/*
 * PSF Font Driver
 *
 * @author: Immanuel Garcia
 *
 */

#include "fontdriver.h"

/* import our font that's in the object file we've created above */
extern char _binary_font_psf_start;
extern char _binary_font_psf_end;
 
uint16 *unicode;
 
void psf_init()
{
    uint16 glyph = 0;
    /* cast the address to PSF header struct */
    PSF_font *font = (PSF_font*)&_binary_font_psf_start;
    /* is there a unicode table? */
    if(font->flags) {
        /* get the offset of the table */
        char *s = (char *)(
          (unsigned char*)&_binary_font_psf_start +
          font->headersize +
          font->numglyph * font->bytesperglyph
        );
        /* allocate memory for translation table */
        unicode = calloc(USHRT_MAX, 2);
        while(s>_binary_font_psf_end) {
            uint16 uc = (uint16)((unsigned char *)s[0]);
            if(uc == 0xFF) {
                glyph++;
                s++;
                continue;
            } else if(uc & 128) {
                /* UTF-8 to unicode */
                if((uc & 32) == 0 ) {
                    uc = ((s[0] & 0x1F)<<6)+(s[1] & 0x3F);
                    s++;
                } else
                if((uc & 16) == 0 ) {
                    uc = ((((s[0] & 0xF)<<6)+(s[1] & 0x3F))<<6)+(s[2] & 0x3F);
                    s+=2;
                } else
                if((uc & 8) == 0 ) {
                    uc = ((((((s[0] & 0x7)<<6)+(s[1] & 0x3F))<<6)+(s[2] & 0x3F))<<6)+(s[3] & 0x3F);
                    s+=3;
                } else
                    uc = 0;
            }
            /* save translation */
            unicode[uc] = glyph;
            s++;
        }
    } else {
        unicode = NULL;
    }
}

/* the linear framebuffer */
char *fb = 0xB8000;
/* number of bytes in each line, it's possible it's not screen width * bytesperpixel! */
int scanline = 800;
/* import our font that's in the object file we've created above */
extern char _binary_font_start;
 
#define PIXEL uint32   /* pixel pointer */
 
void putchar(
    /* note that this is int, not char as it's a unicode character */
    unsigned short int c,
    /* cursor position on screen, in characters not in pixels */
    int cx, int cy,
    /* foreground and background colors, say 0xFFFFFF and 0x000000 */
    uint32 fg, uint32 bg)
{
    /* cast the address to PSF header struct */
    PSF_font *font = (PSF_font*)&_binary_font_psf_start;
    /* we need to know how many bytes encode one row */
    int bytesperline=(font->width+7)/8;
    /* unicode translation */
    if(unicode != NULL) {
        c = unicode[c];
    }
    /* get the glyph for the character. If there's no
       glyph for a given character, we'll display the first glyph. */
    unsigned char *glyph =
     (unsigned char*)&_binary_font_psf_start +
     font->headersize +
     (c>0&&c<font->numglyph?c:0)*font->bytesperglyph;
    /* calculate the upper left corner on screen where we want to display.
       we only do this once, and adjust the offset later. This is faster. */
    int offs =
        (cy * font->height * scanline) +
        (cx * (font->width + 1) * sizeof(PIXEL));
    /* finally display pixels according to the bitmap */
    int x,y, line,mask;
    for(y=0;y<font->height;y++){
        /* save the starting position of the line */
        line=offs;
        mask=1<<(font->width-1);
        /* display a row */
        for(x=0;x<font->width;x++){
            *((PIXEL*)(fb + line)) = *((unsigned int*)glyph) & mask ? fg : bg;
            /* adjust to the next pixel */
            mask >>= 1;
            line += sizeof(PIXEL);
        }
        /* adjust to the next line */
        glyph += bytesperline;
        offs  += scanline;
    }
}