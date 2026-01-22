/*
    singleton.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once
#include <cstdlib>

template <class T>
class t_singleton {
  public:
    static T& instance() {
        if (NULL == _instance) {
            create_instance();
            // atexit( release_instance );
            //  t_singleton 他自己是不会有实例的，无法利用析构函数来释放内存
            //  所以利用 atexit 来在整个程序退出时释放内存
        }
        return *_instance;
    }

  private:
    static void create_instance() {
        if (NULL == _instance) {
            _instance = new T();
        }
    }

    static void release_instance() {
        if (NULL != _instance) {
            delete _instance;
            _instance = NULL;
        }
    }

  private:
    static T* _instance;
};

template <class T>
T* t_singleton<T>::_instance = NULL;
