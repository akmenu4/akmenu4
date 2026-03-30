/*
    flags.h
    Copyright (C) 2008 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>

#define PATCH_DOWNLOAD_PLAY BIT(0)
#define PATCH_CHEATS BIT(1)
#define PATCH_SOFT_RESET BIT(2)
#define PATCH_DMA BIT(3)
#define PATCH_SD_SAVE BIT(4)
#define PATCH_PSRAM BIT(5)
#define PATCH_PROTECTION BIT(6)
#define PATCH_LINKAGE BIT(7)
#define PATCH_SAVE_MASK 0x00001f00
#define PATCH_SAVE_SHIFT 8
#define PATCH_SAVE_NO 0x1f
#define PATCH_LANGUAGE_MASK 0x0000e000
#define PATCH_LANGUAGE_SHIFT 13
// #define PATCH_NEXT          BIT(16)
