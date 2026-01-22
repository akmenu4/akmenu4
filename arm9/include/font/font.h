/*
    font.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <string>
#include "gdi.h"
#include "singleton.h"

class cFont {
  public:
    cFont();
    virtual ~cFont();

  public:
    u32 getStringScreenWidth(const char* str, size_t len);
    std::string breakLine(const std::string& text, u32 maxLineWidth);

  public:
    virtual void Info(const char* aString, u32* aWidth, u32* aSymbolCount) = 0;
    virtual void Draw(u16* mem, s16 x, s16 y, const u8* aText, u16 color) = 0;
    virtual bool Load(const char* aFileName) = 0;
    virtual u32 FontRAM(void);
};
