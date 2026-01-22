/*
    fileicons.cpp
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "fileicons.h"
#include <fat.h>
#include <sys/dir.h>
#include "binaryfind.h"
#include "globalsettings.h"
#include "icons.h"
#include "systemfilenames.h"

cFileIconItem::cFileIconItem(const std::string& aFolderName, const std::string& aFileName)
    : _loaded(false), _foldername(aFolderName), _filename(aFileName) {}

cBMP15& cFileIconItem::Icon(void) {
    Load();
    return _icon;
}

void cFileIconItem::Load(void) {
    if (!_loaded) {
        _icon = createBMP15FromFile(_foldername + _filename + ".bmp");
        _loaded = true;
    }
}

static bool Comp(const cFileIconItem& item1, const cFileIconItem& item2) {
    return strcasecmp(item1.FileName().c_str(), item2.FileName().c_str()) < 0;
}

bool cFileIconItem::operator<(const cFileIconItem& aValue) const {
    return Comp(*this, aValue);
}

cFileIcons::cFileIcons() {
    cIconPaths* paths = new cIconPaths;
    LoadFolder(*paths, SFN_UI_ICONS_DIRECTORY);
    LoadFolder(*paths, SFN_ICONS_DIRECTORY);
    for (cIconPaths::const_iterator it = paths->begin(); it != paths->end(); ++it) {
        _icons.push_back(*it);
    }
    delete paths;
}

void cFileIcons::LoadFolder(cIconPaths& aPaths, const std::string& aFolder) {
    DIR* dir = opendir(aFolder.c_str());
    struct dirent* entry;

    if (NULL != dir) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type != DT_DIR) {
                size_t len = strlen(entry->d_name);
                if (len > 4) {
                    char* extName = entry->d_name + len - 4;
                    if (strcasecmp(extName, ".bmp") == 0) {
                        *extName = 0;
                        aPaths.insert(cFileIconItem(aFolder, entry->d_name));
                    }
                }
            }
        }
        closedir(dir);
    }
}

s32 cFileIcons::Icon(const std::string& aValue) {
    if (!_icons.size()) return -1;
    std::vector<cFileIconItem>::iterator result =
            akui::binary_find(_icons.begin(), _icons.end(), cFileIconItem("", aValue), Comp);
    if (result == _icons.end()) {
        return -1;
    }
    cBMP15& image = (*result).Icon();
    return ((image.valid() && image.width() == 32 && image.height() == 32)
                    ? (result - _icons.begin())
                    : -1);
}

void cFileIcons::Draw(s32 idx, u8 x, u8 y, GRAPHICS_ENGINE engine) {
    gdi().maskBlt(_icons[idx].Icon().buffer(), x, y, 32, 32, engine);
}

void cFileIcons::DrawMem(s32 idx, void* mem) {
    cIcons::maskBlt((const u16*)_icons[idx].Icon().buffer(), (u16*)mem);
}
