/*
    bigclock.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <singleton.h>
#include "bmp15.h"
#include "datetime.h"
#include "ui/window.h"

// class cClockNumber : public
class cBigClock : public akui::cWindow {
  public:
    cBigClock();

    ~cBigClock() {}

  public:
    void init();

    void draw();

    void blinkColon();

    akui::cWindow& loadAppearance(const std::string& aFileName);

  protected:
    void drawNumber(u8 id, u8 number);

    void drawColon();

    cBMP15 _numbers;
    cBMP15 _colon;

    bool _show;
    bool _colonShow;
    bool _ampmShow;
    akui::cPoint _ampmPosition;
    COLOR _ampmColor;
};

typedef t_singleton<cBigClock> bigClock_s;
inline cBigClock& bigClock() {
    return bigClock_s::instance();
}
