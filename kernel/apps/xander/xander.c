#include "xander.h"
#include "../apps.h"

char *title_0 = "XANDER_UI";
char *body_0 = "XANDER_UI HEADERTEST";
int bg_color_0 = 0x4F;
int header_color_0 = 0xF4;

int xander(char **args)
{
    sw_color(bg_color_0);
    clearScreen();
    sw_color(header_color_0);
    centerText(title_0);

    // TOP
    move_cursor(0, 10);
    sw_color(bg_color_0); // 0xbg,fg
    centerText(body_0);
    return 1;
}

void centerText(char *text)
{
    genchar((VGA_LINE / 2) - (strlen(text) / 2), " ");
    printf("%s", text);
    genchar((VGA_LINE / 2) - (strlen(text) / 2) - 1, " ");
}

void genchar(int len, char *character)
{
    int i = 0;
    while (i < len)
    {
        printf(character);
        i++;
    }
}

void centerForm(char *text, int borderColor, int textColor, int bgColor, bool border)
{
    if (border)
    {
        sw_color(bgColor);
        genchar((VGA_LINE / 4), " ");
        sw_color(borderColor);
        genchar(1, " ");
        sw_color(textColor);
        genchar((VGA_LINE / 4) - (strlen(text) / 2) - 1, " ");
        printf("%s", text);
        genchar((VGA_LINE / 4) - (strlen(text) / 2) - 1, " ");
        sw_color(borderColor);
        genchar(1, " ");
        sw_color(bgColor);
        genchar((VGA_LINE / 4), " ");
    }
    if (!border)
    {
        sw_color(bgColor);
        genchar((VGA_LINE / 4), " ");
        sw_color(textColor);
        genchar((VGA_LINE / 4) - (strlen(text) / 2), " ");
        printf("%s", text);
        genchar((VGA_LINE / 4) - (strlen(text) / 2), " ");
        sw_color(bgColor);
        genchar((VGA_LINE / 4), " ");
    }
}

/*
 * EXPECTED RESULT
 * -------------KERNEL PANIC!-------------------
 * 
 *              SYSTEM HALTING!
 * 
 */