/*
    calendarwnd.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include <singleton.h>
#include "ui/form.h"

class cCalendarWnd : public akui::cForm {
  public:
    cCalendarWnd();

    ~cCalendarWnd();

  public:
    cWindow& loadAppearance(const std::string& aFileName);

    void init();

    void draw();

  protected:
    cBMP15 _background;
};

typedef t_singleton<cCalendarWnd> calendarWnd_s;
inline cCalendarWnd& calendarWnd() {
    return calendarWnd_s::instance();
}
