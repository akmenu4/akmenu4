/*
    expwnd.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <string>
#include "dsrom.h"
#include "ui/form.h"
#include "ui/formdesc.h"
#include "ui/message.h"
#include "ui/spinbox.h"
#include "ui/statictext.h"

class cExpWnd : public akui::cForm {
  public:
    cExpWnd(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text);
    ~cExpWnd();

  public:
    void draw();
    bool process(const akui::cMessage& msg);
    cWindow& loadAppearance(const std::string& aFileName);

  protected:
    bool processKeyMessage(const akui::cKeyMessage& msg);
    void onOK();
    void onCancel();
    void onRAM();
    void onSRAM();
    void onShow();
    akui::cButton _buttonOK;
    akui::cButton _buttonCancel;
    akui::cButton _buttonRAM;
    akui::cButton _buttonSRAM;
    akui::cSpinBox _Rumble;
    akui::cStaticText _Label;
    akui::cFormDesc _renderDesc;
    std::string _romName;
};
