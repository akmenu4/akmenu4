/*
    fontfactory.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <font/fontfactory.h>
#include "font_pcf.h"
#include "language.h"
#include "stringtool.h"
#include "systemfilenames.h"

cFontFactory::cFontFactory() : _font(NULL) {}

cFontFactory::~cFontFactory() {
    if (NULL != _font) delete _font;
}

void cFontFactory::makeFont(void) {
    std::string filename(SFN_FONTS_DIRECTORY + lang().GetString("font", "main", SFN_DEFAULT_FONT));
    _font = new cFontPcf();
    _font->Load(filename.c_str());
}
