/*
    cheatwnd.h
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds/ndstypes.h>
#include <vector>

#include "button.h"
#include "form.h"
#include "formdesc.h"
#include "listview.h"
#include "statictext.h"

class cCheatWnd : public akui::cForm {
  public:
    cCheatWnd(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text);
    ~cCheatWnd();
    bool parse(const std::string& aFileName);
    static bool searchCheatData(FILE* aDat, u32 gamecode, u32 crc32, long& aPos, size_t& aSize);
    static bool romData(const std::string& aFileName, u32& aGameCode, u32& aCrc32);
    std::vector<u32> getCheats();
    void writeCheatsToFile(const char* path);

  protected:
    void draw();
    bool process(const akui::cMessage& msg);
    cWindow& loadAppearance(const std::string& aFileName);

  protected:
    bool processKeyMessage(const akui::cKeyMessage& msg);
    void onItemClicked(u32 index);
    void onSelect(void);
    void onDeselectAll(void);
    void onInfo(void);
    void onGenerate(void);
    void onCancel(void);
    void onDraw(const akui::cListView::cOwnerDraw& data);
    void drawMark(const akui::cListView::cOwnerDraw& od, u16 width);
    void generateList(void);
    akui::cButton _buttonDeselect;
    akui::cButton _buttonInfo;
    akui::cButton _buttonGenerate;
    akui::cButton _buttonCancel;
    akui::cFormDesc _renderDesc;
    akui::cListView _List;

  protected:
    bool parseInternal(FILE* aDat, u32 gamecode, u32 crc32);
    void deselectFolder(size_t anIndex);

  private:
    struct sDatIndex {
        u32 _gameCode;
        u32 _crc32;
        u64 _offset;
    };
    class cParsedItem {
      public:
        std::string _title;
        std::string _comment;
        std::vector<u32> _cheat;
        u32 _flags;
        u32 _offset;
        cParsedItem(const std::string& title, const std::string& comment, u32 flags, u32 offset = 0)
            : _title(title), _comment(comment), _flags(flags), _offset(offset) {};
        enum { EFolder = 1, EInFolder = 2, EOne = 4, ESelected = 8, EOpen = 16 };
    };
    enum {
        EIconColumn = 0,
        ETextColumn = 1,
        EIconWidth = 15,
        EFolderWidth = 11,
        ERowHeight = 15,
        EFolderTop = 3,
        ESelectTop = 5
    };

  private:
    std::vector<cParsedItem> _data;
    std::vector<size_t> _indexes;
    std::string _fileName;
};
