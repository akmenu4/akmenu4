/*
    datetime.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>
#include <singleton.h>
#include <time.h>
#include "stringtool.h"

class cDateTime {
  private:
    tm iTimeParts;

  private:
    void FillTimeParts(void);

  public:
    cDateTime() {}
    ~cDateTime() {}

  public:
    static const char* weekdayStrings[];
    u16 year(void);
    u8 month(void);
    u8 day(void);
    u8 weekday(void);

    u8 hours(void);
    u8 minutes(void);
    u8 seconds(void);

    std::string getDateString(void);
    std::string getTimeString(void);
    std::string getTimeStampString(void);
};

typedef t_singleton<cDateTime> dateTime_s;
inline cDateTime& datetime() {
    return dateTime_s::instance();
}
