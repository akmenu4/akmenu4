/*
    userinput.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "userinput.h"
#include <cstring>
#include "dbgtool.h"
#include "timer.h"
#include "ui/keymessage.h"
#include "ui/windowmanager.h"

using namespace akui;

static INPUT inputs;
static INPUT lastInputs;
static double lastInputTime;
static u32 idleMs;

void initInput() {
    lastInputTime = 0;
    idleMs = 0;
    keysSetRepeat(30, 1);
}

INPUT& updateInput() {
    memset(&inputs, 0, sizeof(inputs));
    touchRead(&inputs.touchPt);
    if (inputs.touchPt.px == 0 && inputs.touchPt.py == 0) {
        if (lastInputs.touchHeld) {
            inputs.touchUp = true;
            inputs.touchPt = lastInputs.touchPt;
            dbg_printf("getInput() Touch UP! %d %d\n", inputs.touchPt.px, inputs.touchPt.py);
        } else {
            inputs.touchUp = false;
        }
        inputs.touchDown = false;
        inputs.touchHeld = false;
    } else {
        if (!lastInputs.touchHeld) {
            inputs.touchDown = true;
            dbg_printf("getInput() Touch DOWN! %d %d\n", inputs.touchPt.px, inputs.touchPt.py);
        } else {
            inputs.movedPt.px = inputs.touchPt.px - lastInputs.touchPt.px;
            inputs.movedPt.py = inputs.touchPt.py - lastInputs.touchPt.py;
            inputs.touchMoved = (0 != inputs.movedPt.px) || (0 != inputs.movedPt.py);
            inputs.touchDown = false;
        }
        inputs.touchUp = false;
        inputs.touchHeld = true;
    }
    // dbg_printf( "touch x %d y %d\n", inputs.touchPt.px, inputs.touchPt.py );
    // dbg_printf( "touchdown %d clicked %d\n", inputs.touchDown, inputs.clicked );
    scanKeys();
    inputs.keysDown = keysDown();
    inputs.keysUp = keysUp();
    inputs.keysHeld = keysHeld();
    inputs.keysDownRepeat = keysDownRepeat();
    if (lastInputs == inputs) {
        idleMs = (u32)((timer().getTime() - lastInputTime) * 1000);
    } else {
        // dbg_printf( "input idled %d\n", idleMs );
        resetInputIdle();
    }
    lastInputs = inputs;

    return inputs;
}

INPUT& getInput() {
    return inputs;
}

u32 getInputIdleMs() {
    return idleMs;
}

void resetInputIdle(void) {
    lastInputTime = timer().getTime();
    idleMs = 0;
}

bool processInput(INPUT& inputs) {
    bool ret = false;
    unsigned char shift = 0;

    if (inputs.keysHeld & KEY_L) shift |= cKeyMessage::UI_SHIFT_L;

    if (inputs.keysDown & KEY_A)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_A, shift);
    if (inputs.keysDown & KEY_B)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_B, shift);
    if (inputs.keysDown & KEY_X)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_X, shift);
    if (inputs.keysDown & KEY_Y)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_Y, shift);
    if (inputs.keysDown & KEY_R)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_R, shift);
    if (inputs.keysDown & KEY_L)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_L, shift);
    if (inputs.keysDown & KEY_START || inputs.keysDownRepeat & KEY_START)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_START, shift);
    if (inputs.keysDown & KEY_SELECT)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_SELECT, shift);
    if (inputs.keysDown & KEY_LEFT || inputs.keysDownRepeat & KEY_LEFT)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_LEFT, shift);
    if (inputs.keysDown & KEY_RIGHT || inputs.keysDownRepeat & KEY_RIGHT)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_RIGHT, shift);
    if (inputs.keysDown & KEY_UP || inputs.keysDownRepeat & KEY_UP)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_UP, shift);
    if (inputs.keysDown & KEY_DOWN || inputs.keysDownRepeat & KEY_DOWN)
        ret = ret || windowManager().onKeyDown(cKeyMessage::UI_KEY_DOWN, shift);

    if (inputs.keysUp & KEY_L) ret = ret || windowManager().onKeyUp(cKeyMessage::UI_KEY_L, shift);

    if (inputs.touchDown)
        ret = ret || windowManager().onTouchDown(inputs.touchPt.px, inputs.touchPt.py);
    if (inputs.touchUp)
        ret = ret || windowManager().onTouchUp(inputs.touchPt.px, inputs.touchPt.py);
    if (inputs.touchMoved)
        ret = ret || windowManager().onTouchMove(inputs.movedPt.px, inputs.movedPt.py);

    if (inputs.keysDown & KEY_LID) {
        dbg_printf("lid closed\n");
        fifoSendValue32(FIFO_PM, PM_REQ_SLEEP);
        swiDelay(8380000);  // 500ms
        /*
        powerOff(0x3f);
        powerOn(0x10);
        */
    } else if (inputs.keysUp & KEY_LID) {
        dbg_printf("lid opened\n");
        /*
        powerOff(0x3f);
        powerOn(0x0f);
        */
    }

    return ret;
}
