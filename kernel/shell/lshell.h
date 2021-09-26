#ifndef LSHELL_H
#define LSHELL_H

#include "include/types/types.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/screen/screen.h"
#include "include/utils.h"
#include "fs/vfs.h"
#include "kernel/panic.h"
#include "drivers/rtc/rtc.h"
#include "drivers/mouse/mouse.h"
#include "fs/fs.h"
#include "drivers/acpi/acpi.c"

void lsh_loop();

#endif
