/*
    Copyright (C) 2007 Acekard, www.acekard.com

    SPDX-License-Identifier: MIT
*/

#pragma once

#include <nds/bios.h>
#include <nds/ndstypes.h>

inline void fillMemory(void* addr, u32 count, u32 value) {
    swiFastCopy((void*)(&value), addr, (count >> 2) | COPY_MODE_WORD | COPY_MODE_FILL);
}

inline void zeroMemory(void* addr, u32 count) {
    fillMemory(addr, count, 0);
}
