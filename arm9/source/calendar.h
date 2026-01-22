/*
    calendar.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "bmp15.h"
#include "datetime.h"
#include "singleton.h"
#include "ui/point.h"
#include "ui/window.h"

class cCalendar : public akui::cWindow {
  public:
    cCalendar();

    ~cCalendar() {}

  public:
    void init();

    void draw();

    akui::cWindow& loadAppearance(const std::string& aFileName);

  protected:
    u8 weekDayOfFirstDay();

    void drawDayNumber(u8 day);
    void drawText(const akui::cPoint& position, u32 value, u32 factor);
    void drawNumber(const akui::cPoint& position, u32 index, u32 value);

    akui::cPoint _dayPosition;
    akui::cSize _daySize;
    akui::cPoint _dayxPosition;
    akui::cPoint _monthPosition;
    akui::cPoint _yearPosition;
    COLOR _dayHighlightColor;
    cBMP15 _dayNumbers;  // index 10 means colon
    cBMP15 _yearNumbers;

    bool _showYear;
    bool _showMonth;
    bool _showDayX;
    bool _showDay;

    bool _colonShow;
};

typedef t_singleton<cCalendar> calendar_s;
inline cCalendar& calendar() {
    return calendar_s::instance();
}
