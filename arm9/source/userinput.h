/*
    userinput.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds.h>

typedef struct T_INPUT {
    struct touchPositionRelative {
        s16 px;
        s16 py;
    };
    u32 keysHeld;
    u32 keysUp;
    u32 keysDown;
    u32 keysDownRepeat;
    touchPosition touchPt;
    touchPositionRelative movedPt;
    bool touchDown;
    bool touchUp;
    bool touchHeld;
    bool touchMoved;
    bool operator==(const T_INPUT& src) const {
        return keysHeld == src.keysHeld && keysUp == src.keysUp && keysDown == src.keysDown &&
               keysDownRepeat == src.keysDownRepeat && touchPt.px == src.touchPt.px &&
               touchPt.py == src.touchPt.py && movedPt.px == src.movedPt.px &&
               movedPt.py == src.movedPt.py && touchDown == src.touchDown &&
               touchUp == src.touchUp && touchHeld == src.touchHeld && touchMoved == src.touchMoved;
    }
} INPUT;

void initInput();
INPUT& updateInput();
INPUT& getInput();
u32 getInputIdleMs();
void resetInputIdle(void);
bool processInput(INPUT& inputs);
