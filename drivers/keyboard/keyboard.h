/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "keycodes.h"
#include "include/types/types.h"

string readStr();
string readStrShell(bool prompt, string buffstr);
string textedit_readStr();

#endif