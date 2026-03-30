/*
    listview.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <string>
#include <vector>
#include "window.h"

namespace akui {
class cListColumn {
  public:
    cListColumn() : index(0), width(0), offset(0), text("") {}

    u32 index;
    u16 width;
    u16 offset;
    std::string text;
};

class cListItem {
  protected:
    std::string _text;
    u32 _lines;

  public:
    cListItem() : _text(""), _lines(1), index(0), column(0), imageId(0), param(0) {}
    u32 index;
    u32 column;
    u32 imageId;
    u32 param;
    const std::string& text(void) const { return _text; }
    u32 lines(void) const { return _lines; }
    void setText(const std::string& text);
};

class cListView : public cWindow {
  public:
    cListView(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text);

    virtual ~cListView() {}

    typedef std::vector<cListItem> itemVector;  // a column

  public:
    class cOwnerDraw {
      public:
        size_t _row;
        size_t _col;
        cPoint _position;
        cSize _size;
        s16 _textY;
        u16 _textHeight;
        const char* _text;
        GRAPHICS_ENGINE _engine;
        cOwnerDraw(size_t row, size_t col, const cPoint& position, const cSize& size, s16 textY,
                   u16 textHeight, const char* text, GRAPHICS_ENGINE engine)
            : _row(row),
              _col(col),
              _position(position),
              _size(size),
              _textY(textY),
              _textHeight(textHeight),
              _text(text),
              _engine(engine) {};
    };

  public:
    void draw();

    bool insertColumn(size_t index, const std::string& text, u8 width);

    bool insertRow(size_t index, const std::vector<std::string>& text);

    void removeRow(size_t index);  // return id of the item next to the removed item

    void removeAllRows();

    u32 getRowCount() { return _rows.size(); }

    void setRowHeight(u16 height) {
        _rowHeight = height;
        setListViewSize(_size.x, _size.y);
    }

    void setListViewSize(u16 w, u16 h) {
        setSize(cSize(w, h));
        _visibleRowCount = h / _rowHeight;
        // if( _visibleRowCount > _rows.size() ) _visibleRowCount = _rows.size();
    }

    void arangeColumnsSize();

    void selectRow(int id);

    u32 firstVisibleRowId(void) { return _firstVisibleRowId; }

    u32 selectedRowId(void) { return _selectedRowId; }

    void selectNext() { selectRow(_selectedRowId + 1); }

    void selectPrev() { selectRow(_selectedRowId - 1); }

    u32 rowBelowPoint(const cPoint& pt);

    void scrollTo(int id);

    u32 visibleRowCount() { return _visibleRowCount; }

    cWindow& loadAppearance(const std::string& aFileName);

    bool process(const akui::cMessage& msg);

    inline void setColors(u16 textColor, u16 textColorHilight, u16 selectionBarColor1,
                          u16 selectionBarColor2) {
        _textColor = textColor;
        _textColorHilight = textColorHilight;
        _selectionBarColor1 = selectionBarColor1;
        _selectionBarColor2 = selectionBarColor2;
    };

    void setFirstVisibleIdAndSelectRow(u32 first, u32 row);

    Signal1<u32> selectedRowClicked;

    Signal1<u32> selectChanged;

    Signal1<u32> scrolled;

    Signal1<const cOwnerDraw&> ownerDraw;

  protected:
    virtual void onSelectChanged(u32 index) {}

    virtual void onSelectedRowClicked(u32 index) {}

    virtual void onScrolled(u32 index) {}

    bool processTouchMessage(const akui::cTouchMessage& msg);

  protected:
    void drawSelectionBar();

    void drawText();

  protected:
    std::string _text;
    u16 _rowHeight;
    u16 _textColor;
    u16 _textColorHilight;
    u16 _selectionBarColor1;
    u16 _selectionBarColor2;
    u16 _selectionBarOpacity;

    u32 _selectedRowId;
    u32 _firstVisibleRowId;
    u32 _visibleRowCount;
    u16 _rowsPerpage;
    bool _touchMovedAfterTouchDown;

    std::vector<cListColumn> _columns;
    std::vector<itemVector> _rows;
};

}  // namespace akui
