#include "xgui.h"
#include "../apps.h"

char *title = "The Quick Man";
char *formTitle = "The Quick Brown Fox";
char *body = " The Quick Brown Fox Jumps Over"; // 38 Chars MAX
int bg_color = 0x3F;
int in_bodyColor = 0x7F;
int border_color = 0x1F;

int xgui(char **args)
{
    sw_color(bg_color);
    clearScreen();
    sw_color(0x5F);
    centerText(title);
    sw_color(bg_color);

    // TOP
    move_cursor(0, 10);
    centerForm(" ", border_color, border_color, bg_color, false, false, 0);

    // TITLE
    move_cursor(0, 11);
    centerForm(formTitle, border_color, border_color, bg_color, false, true, 0);

    // BODY PADDING (TOP)
    move_cursor(0, 12);
    centerForm(" ", border_color, in_bodyColor, bg_color, true, true, 0);

    // BODY
    move_cursor(0, 13);
    sw_color(in_bodyColor);
    centerForm(body, border_color, in_bodyColor, bg_color, true, true, 0);

    // BODY2
    move_cursor(0, 14);
    sw_color(in_bodyColor);
    centerForm("The Lazy Dog", border_color, in_bodyColor, bg_color, true, true, 1);

    // BODY PADDING (BOTTOM)
    move_cursor(0, 15);
    centerForm(" ", border_color, in_bodyColor, bg_color, true, true, 0);

    // BOTTOM
    move_cursor(0, 16);
    centerForm(" ", border_color, border_color, bg_color, false, true, 0);
    genShadow(bg_color);
    return 1;
}

/*
 * EXPECTED RESULT
 * -------------------------------------
 * -------------HELLO-------------------
 * -------------------------------------
 * -		EAGO		       -
 * -------------------------------------
 */