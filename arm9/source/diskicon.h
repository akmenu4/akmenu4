/*
    diskicon.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include <singleton.h>
#include "sprite.h"
#include "ui/window.h"

class cDiskIcon : public akui::cWindow {
  public:
    cDiskIcon();

    ~cDiskIcon() {}

  public:
    void draw();

    void turnOn();

    void turnOff();

    akui::cWindow& loadAppearance(const std::string& aFileName);

    void blink(void);

  protected:
    bool _draw;

    float _lightTime;

    cSprite _icon;
};

typedef t_singleton<cDiskIcon> diskIcon_s;
inline cDiskIcon& diskIcon() {
    return diskIcon_s::instance();
}
