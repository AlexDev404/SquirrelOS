/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#ifndef APPS_H
#define APPS_H

#include "drivers/screen/screen.h"
#include "include/types/types.h"
#include "include/math/math.h"
#include "drivers/keyboard/keyboard.h"
#include "include/memory/memory.h"

// INCLUDE APPS BELOW THIS LINE HERE!
// MAKE SURE TO EDIT BUILD.SH AFTER ADDING!!!

#include "calculator/calculator.h"
#include "cowsay/cowsay.h"
#include "man/man.h"
#include "xgui/xgui.h"
#include "xander/xander.h"
#include "../../include/string/string.h"

int VGA_LINE = (VGA_WIDTH / 10) - 5;

/************************************/

int (*builtin_appFunc[])(char **) = {
    &calculator,
    &ccowsay,
    &man,
    &xgui,
    &xander};

char *builtin_apps[] = {
    "calculator",
    "ccowsay",
    "man",
    "xgui",
    "xander"};

int num_builtin_apps()
{
    return sizeof(builtin_apps) / sizeof(char *);
}

int appLaunch(char **args, bool direct);

#endif