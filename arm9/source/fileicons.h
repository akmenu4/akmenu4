/*
    fileicons.h
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <singleton.h>
#include <set>
#include <vector>
#include "bmp15.h"
#include "gdi.h"

class cFileIconItem {
  public:
    cFileIconItem() : _loaded(false) {};
    cFileIconItem(const std::string& aFolderName, const std::string& aFileName);
    const std::string& FileName(void) const { return _filename; };
    const std::string& FolderName(void) const { return _foldername; };
    cBMP15& Icon(void);
    bool operator<(const cFileIconItem& aValue) const;

  private:
    void Load(void);

  private:
    bool _loaded;
    std::string _foldername;
    std::string _filename;
    cBMP15 _icon;
};

class cFileIcons {
  public:
    cFileIcons();
    s32 Icon(const std::string& aValue);
    void Draw(s32 idx, u8 x, u8 y, GRAPHICS_ENGINE engine);
    void DrawMem(s32 idx, void* mem);

  private:
    std::vector<cFileIconItem> _icons;

  private:
    typedef std::set<cFileIconItem> cIconPaths;
    static void LoadFolder(cIconPaths& aPaths, const std::string& aFolder);
};

typedef t_singleton<cFileIcons> fileIcons_s;
inline cFileIcons& fileIcons() {
    return fileIcons_s::instance();
}
