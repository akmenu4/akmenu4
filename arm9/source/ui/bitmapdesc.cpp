/*
    bitmapdesc.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "bitmapdesc.h"
#include <memtool.h>
#include "dbgtool.h"

namespace akui {

///////////////////////////////// desc ////////////////
cBitmapDesc::cBitmapDesc() {
    _bltmode = BM_BITBLT;
}

cBitmapDesc::~cBitmapDesc() {}

void cBitmapDesc::draw(const cRect& area, GRAPHICS_ENGINE engine) const {
    if (_background.valid()) {
        if (BM_BITBLT == _bltmode)
            gdi().bitBlt(_background.buffer(), area.position().x, area.position().y,
                         _background.width(), _background.height(), engine);
        else
            gdi().maskBlt(_background.buffer(), area.position().x, area.position().y,
                          _background.width(), _background.height(), engine);
    }
}

void cBitmapDesc::loadData(const std::string& filename) {
    if (!_background.valid()) {
        _background = createBMP15FromFile(filename);
    }
}

cSize cBitmapDesc::size() {
    if (_background.valid())
        return cSize(_background.width(), _background.height());
    else
        return cSize(0, 0);
}

}  // namespace akui
