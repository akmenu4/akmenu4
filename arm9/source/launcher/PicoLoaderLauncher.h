/*
    Copyright (C) 2024 lifehackerhansol

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <nds/ndstypes.h>
#include <string>

#include <picoLoader7.h>

#include "ILauncher.h"

class PicoLoaderLauncher : public ILauncher {
  public:
    bool launchRom(std::string romPath, std::string savePath, u32 flags, u32 cheatOffset,
                   u32 cheatSize) override;

  private:
    void copyToVram(const char* loaderPath, void* destination);
    bool prepareCheats(void);
    bool setParameters(void);
    std::string mRomPath;
    std::string mSavePath;
    u32 mFlags;
    pload_cheats_t* mCheats;
};
