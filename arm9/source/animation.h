/*
    animation.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "ui/ui.h"

class cAnimation {
  public:
    cAnimation();

    virtual ~cAnimation();

  public:
    virtual void update() = 0;

    void show();

    void hide();

    bool visible() { return _visible; }

  protected:
    akui::cPoint _position;
    akui::cSize _size;
    bool _visible;
};

class cAnimationManager {
  public:
    cAnimationManager();

    ~cAnimationManager();

  public:
    void update();

    void addAnimation(cAnimation* animation);

    void removeAnimation(cAnimation* animation);

  protected:
    std::list<cAnimation*> _animations;
};

typedef t_singleton<cAnimationManager> animationManager_s;
inline cAnimationManager& animationManager() {
    return animationManager_s::instance();
}
