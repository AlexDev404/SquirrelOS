#ifndef XANDER_H
#define XANDER_H
#include "include/types/types.h"

int xander(char **args);
void centerText(char *text);
void genchar(int len, char *character);
void centerForm(char *text, int borderColor, int textColor, int bgColor, bool border, bool shadow, int offset);
void genShadow(int bgColor);
#endif