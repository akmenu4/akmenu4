/*
    binaryfind.h
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <algorithm>

namespace akui {
template <typename Iterator, typename T, typename Compare>
Iterator binary_find(Iterator first, Iterator last, const T& value, Compare cmp) {
    Iterator result = std::lower_bound(first, last, value, cmp);
    if (result == last)
        return last;
    else if (!cmp(value, *result))
        return result;
    else
        return last;
}
}  // namespace akui
