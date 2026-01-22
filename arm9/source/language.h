/*
    language.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <singleton.h>
#include "dbgtool.h"
#include "globalsettings.h"
#include "inifile.h"
#include "stringtool.h"
#include "systemfilenames.h"
#include "timetool.h"

class cLanguageFile : public CIniFile {
  public:
    cLanguageFile() {
        m_bReadOnly = true;
        LoadIniFile(SFN_LANGUAGE_TEXT);
    }
    ~cLanguageFile() {};
};

typedef t_singleton<cLanguageFile> languageFile_s;
inline cLanguageFile& lang() {
    return languageFile_s::instance();
}
#define LANG(i, t) lang().GetString(i, t, t)

bool stringComp(const std::string& item1, const std::string& item2);
