#pragma once

/*!
 * @file s-basic.h
 * @brief SBband時追加された基本事項のヘッダーファイル /
 * The most basic "include" file. This file simply includes other low level header files.
 * @date 2021/01/09
 * @author
 * 火炎の飛竜
 */

/* enum2i i2enumは頻繁に使うのでこっちに（本家に取り込むかは不明）*/
#include "util/enum-converter.h"
#include <stdexcept>
#include <unordered_map>

#if _MSVC_LANG < 202002L && __cplusplus < 202002L
/* C++17以前用のunordered_mapクラス */

namespace sb_std {
using namespace std;
template <typename T, typename M>
class unordered_map : public std::unordered_map<T, M> {
    using std::unordered_map<T, M>::unordered_map;

public:
    bool contains(T key) const
    {
        try {
            this->at(key);
            return true;
        } catch (std::out_of_range &) {
            return false;
        }
    };
};
}

#else

#define sb_std std

#endif
