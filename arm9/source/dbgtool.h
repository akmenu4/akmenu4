/*
    dbgtool.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// #define DEBUG

#ifdef DEBUG
static inline int dbg_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vfprintf(stderr, format, args);
    va_end(args);
    return ret;
}
#else
#define dbg_printf(...)
#endif  // DEBUG

#ifdef DEBUG
static inline void _cwl(const char* file, int line) {
    const char* seek = file;

    while (*seek != 0) {
        if (*seek == '/') file = seek;
        seek++;
    }
    dbg_printf("%s(%d)\n", file, line);
}
#define cwl() \
    ;         \
    _cwl(__FILE__, __LINE__);
#else
#define cwl()
#endif  // DEBUG

#ifdef DEBUG
static inline void wait_press_b() {
    dbg_printf("\npress B to continue.\n");
    scanKeys();
    u16 keys_up = 0;
    while (0 == (keys_up & KEY_B)) {
        scanKeys();
        keys_up = keysUp();
    }
}
#else
#define wait_press_b()
#endif  // DEBUG
