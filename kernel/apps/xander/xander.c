/*
 *
 * @name: LibXander v0.0.5A
 * @author: Immanuel Garcia
 * @desc: An NCurses-like Text-GUI Framework for SquirrelOS
 * @license: GPL v2.0
 * 
 */

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

void genShadow(int bgColor)
{

    sw_color(bgColor);
    genchar((VGA_LINE / 4), " ");
    sw_color(0x00);
    genchar((VGA_LINE / 4) + 2, " ");
    genchar((VGA_LINE / 4), " ");
    sw_color(bgColor);
    genchar((VGA_LINE / 4), " ");
}

void centerForm(char *text, int borderColor, int textColor, int bgColor, bool border, bool shadow, int offset)
{
    if (border)
    {
        sw_color(bgColor);
        genchar((VGA_LINE / 4), " "); // Q1
        sw_color(borderColor);
        genchar(1, " ");
        sw_color(textColor);
        genchar((VGA_LINE / 4) - (strlen(text) / 2) - 1, " "); // Q2
        printf("%s", text);
        genchar((VGA_LINE / 4) - (strlen(text) / 2) - 1 + offset, " "); // Q3
        sw_color(borderColor);
        genchar(1, " ");

        // If shadow is requested, add it

        if (shadow)
        {
            sw_color(0x00);
            genchar(2, " ");

            // Account for shadow

            sw_color(bgColor);
            genchar((VGA_LINE / 4) - 2, " "); // Q4
        }
        else
        {
            sw_color(bgColor);
            genchar((VGA_LINE / 4), " "); // Q4
        }
    }
    if (!border)
    {
        // Split screen into 4 quarters
        sw_color(bgColor);
        genchar((VGA_LINE / 4), " "); // First quarters
        sw_color(textColor);
        genchar((VGA_LINE / 4) - (strlen(text) / 2), " "); // Second Quarters
        printf("%s", text);
        genchar((VGA_LINE / 4) - (strlen(text) / 2) + offset, " "); // Third Quarters

        // If shadow is requested, add it

        if (shadow)
        {
            sw_color(0x00);
            genchar(2, " ");

            // Account for shadow

            sw_color(bgColor);
            genchar((VGA_LINE / 4) - 2, " "); // Fourth Quarters
        }

        else
        {
            sw_color(bgColor);
            genchar((VGA_LINE / 4), " "); // Fourth Quarters
        }
    }
}

/*
 * EXPECTED RESULT
 * -------------KERNEL PANIC!-------------------
 * 
 *              SYSTEM HALTING!
 * 
 */