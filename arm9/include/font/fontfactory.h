/*
    fontfactory.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <nds.h>

#include <singleton.h>

#include <font/font.h>
class cFontFactory {
  public:
    cFontFactory();

    ~cFontFactory();

    void makeFont(void);

    cFont& font() { return *_font; }

  protected:
    cFont* _font;
};

typedef t_singleton<cFontFactory> fontFactory_s;
inline cFontFactory& fontFactory() {
    return fontFactory_s::instance();
}
inline cFont& font() {
    return fontFactory_s::instance().font();
}
