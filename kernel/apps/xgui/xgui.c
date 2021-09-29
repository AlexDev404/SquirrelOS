#include "xgui.h"
#include "../apps.h"

char *title = "The Quick";
char *body = "Job hatted bearded";
int bg_color = 0x3F;
int in_bodyColor = 0x7F;
int border_color = 0x9F;

int xgui(char **args)
{
    sw_color(bg_color);
    clearScreen();
    printf("%s\n", title);
    genchar((strlen(title)+1), "_");
    printf("\n");
    genchar((strlen(title)+1)*2, "_");
    // move_cursor(VGA_WIDTH/2, VGA_HEIGHT/2);

// TOP    
    move_cursor(20, 10);
    sw_color(border_color); // 0xbg,fg
    genchar((strlen(title) + strlen(body))*2, " ");


// TITLE    
    move_cursor(20, 11);
    genchar((strlen(title)/2) + strlen(body), " ");
    printf("%s ", title);
    genchar((strlen(title)/2) + strlen(body), " ");

// BODY
    move_cursor(20, 12);
    printf(" ");
    sw_color(in_bodyColor);
    genchar((strlen(title) + (strlen(body)/2))-1, " ");
    printf("%s", body);
    genchar((strlen(title) + (strlen(body)/2))-1, " ");
    sw_color(border_color); // 0xbg,fg
    printf(" ");

// BOTTOM
    move_cursor(20, 13);
    genchar((strlen(title) + strlen(body))*2, " ");
    move_cursor(0, 20);
    return 1;
}

void genchar(int len, char *character){
	int i = 0;
	while(i < len){
		printf(character);
		i++;
}
}

/*
 * EXPECTED RESULT
 * -------------------------------------
 * -------------HELLO-------------------
 * -------------------------------------
 * -		EAGO		       -
 * -------------------------------------
 */