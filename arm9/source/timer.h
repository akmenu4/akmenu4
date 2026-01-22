/*
    timer.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include <singleton.h>

class cTimer {
  public:
    cTimer();

    ~cTimer() {}

  public:
    void initTimer();

    double updateTimer();

    double updateFps();

    double getFps();

    double getTime();

    vu64 getTick();

    double tickToUs(u64 tick);

  private:
    static void timerInterruptHandler();
    double _lastTime;
    double _currentTime;
    static vu64 _overFlow;
    const double _factor = 1.f / (33.514 * 1000000.f);
    double _fps;
    u32 _fpsCounter;
};

typedef t_singleton<cTimer> timer_s;
inline cTimer& timer() {
    return timer_s::instance();
}
