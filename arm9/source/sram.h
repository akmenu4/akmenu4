/*
    sram.h
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include <stdio.h>

#define SRAM_PAGES 128
#define SRAM_SAVE_PAGES 32
#define SRAM_PAGE_SIZE 0x1000
#define SRAM_SAVE_SIZE SRAM_SAVE_PAGES* SRAM_PAGE_SIZE
#define SAVE_GBA_HEADER_MAGIC 0x42474b41

class cSram {
  public:
    struct sSaveInfo {
        u32 marker;
        u32 offset;
        u32 size;
        u32 header;
        sSaveInfo() : marker(SAVE_GBA_HEADER_MAGIC), offset(0), size(SRAM_SAVE_SIZE), header(0) {};
        sSaveInfo(u32 aSize) : marker(SAVE_GBA_HEADER_MAGIC), offset(0), size(aSize), header(0) {};
    };

  public:
    static void SaveSramToFile(const char* romName, u16 aStartPage);
    static void LoadSramFromFile(const char* romName, u16 aStartPage);
    static void CreateDefaultFile(const char* romName, u32 size);
    static u8* SaveSramToMemory(u16 aStartPage, sSaveInfo& aSaveInfo, bool aShowProgress);
    static void ProcessRAW(FILE* aFile, sSaveInfo& anInfo);

  private:
    static bool SaveFileName(const char* romName, char* saveName);
    static void BlankSram(u16 aStartPage);
    static void NormalizeSize(sSaveInfo& anInfo);
};
