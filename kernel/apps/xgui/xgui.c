#include "xgui.h"
#include "../apps.h"

char *title = "The Quick";
char *body = "Job hatted bearded man";

int xgui(char **args)
{
    sw_color(0x1F);
    clearScreen();
    printf("%s\n", title);
    genchar(strlen(title), "_");
    // move_cursor(VGA_WIDTH/2, VGA_HEIGHT/2);

// TOP    
    move_cursor(20, 10);
    sw_color(0x4F); // 0xbg,fg
    genchar((strlen(title) + strlen(body))*2, " ");


// TITLE    
    move_cursor(20, 11);
    genchar((strlen(title)/2) + strlen(body), " ");
    printf("%s ", title);
    genchar((strlen(title)/2) + strlen(body), " ");

// BODY
    move_cursor(20, 12);
    printf(" ");
    sw_color(0x7F);
    genchar((strlen(title) + (strlen(body)/2))-1, " ");
    printf("%s", body);
    genchar((strlen(title) + (strlen(body)/2))-1, " ");
    sw_color(0x4F); // 0xbg,fg
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