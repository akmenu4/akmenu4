/*
    point.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <algorithm>

namespace akui {
template <typename T>
class t_point {
  public:
    typedef T value_type;
    value_type x;
    value_type y;

    t_point() : x(), y() {}
    t_point(value_type x, value_type y) : x(x), y(y) {}
    t_point(const t_point& p) { x = p.x, y = p.y; }
    t_point operator+(const t_point& p) const { return t_point(x + p.x, y + p.y); }
    t_point operator-(const t_point& p) const { return t_point(x - p.x, y - p.y); }
    bool operator==(const t_point& p) const { return (x == p.x) && (y == p.y); }
    bool operator!=(const t_point& p) const { return (x != p.x) || (y != p.y); }
    t_point& operator+=(const t_point& p) {
        x += p.x, y += p.y;
        return *this;
    }
    t_point& operator-=(const t_point& p) {
        x -= p.x, y -= p.y;
        return *this;
    }
    t_point& operator=(const t_point& p) {
        x = p.x, y = p.y;
        return *this;
    }
    // 当前点是否在p的左侧
    bool is_left(const t_point& p) const { return x < p.x; }  // 是否在点的左边
    // 当前点是否在p的右侧
    bool is_right(const t_point& p) const { return x > p.x; }  // 是否在点的右边
    // 当前点是否在p的上方
    bool is_up(const t_point& p) const { return y < p.y; }  // 是否在点的上边
    // 当前点是否在p的下方
    bool is_down(const t_point& p) const { return y > p.y; }  // 是否在点的下边
    t_point& operator()(value_type x_, value_type y_) {
        x = x_;
        y = y_;
        return *this;
    }
};

// point
typedef t_point<int> cPoint;
typedef t_point<float> cPointf;
// size
typedef t_point<int> cSize;

}  // namespace akui
