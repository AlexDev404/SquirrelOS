/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#ifndef APPS_H
#define APPS_H

#include "drivers/screen/screen.h"
#include "fs/fs.h"
#include "include/types/types.h"
#include "include/math/math.h"
#include "drivers/keyboard/keyboard.h"
#include "include/utils.h"

// INCLUDE APPS BELOW THIS LINE HERE!
// MAKE SURE TO EDIT BUILD.SH AFTER ADDING!!!

#include "textedit/textedit.h"
#include "calculator/calculator.h"
#include "serialapp/serialapp.h"
#include "slang/slang.h"
#include "cowsay/cowsay.h"
#include "man/man.h"

/************************************/

int (*builtin_appFunc[])(char **) = {
    &textedit,
    &calculator,
    &serialapp,
    &slang,
    &ccowsay,
    &man};

char *builtin_apps[] = {
    "textedit",
    "calculator",
    "serialapp",
    "slang",
    "ccowsay",
    "man"};

int num_builtin_apps()
{
    return sizeof(builtin_apps) / sizeof(char *);
}

int appLaunch(char **args, bool direct);

#endif