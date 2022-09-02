// ----------------------------------------------------------------------------
// ____                               _
// |  _\                             | |
// | |_)| __ _ ___  ___  ___ ___   __| | ___ TM
// |  _< / _` / __|/ _ \/ __/ _ \ / _` |/ _ \
// | |_)| (_| \__ \  __/ (_| (_) | (_| |  __/
// |____/\__,_|___/\___|\___\___/ \__,_|\___|
//
//      F O U N D A T I O N   P R O J E C T
//
// Copyright (C) 2020 Jeff Panici
// All rights reserved.
//
// This software source file is licensed under the terms of MIT license.
// For details, please read the LICENSE file.
//
/*
这个文件定义了一些东西的切片,部分含义的东西

*/
// ----------------------------------------------------------------------------

#pragma once

#include <cstring>
#include <basecode/core/types.h>
#include <basecode/core/hashable.h>
#include <basecode/core/hash/murmur.h>
#include <basecode/core/format_types.h>

#define WITH_SLICE_AS_CSTR(Slice, Code) \
        [&](str::slice_t s) -> void {                               \
            s8 Slice[s.length + 1];                                 \
            std::memcpy(Slice, s.data, s.length);                   \
            Slice[s.length] = '\0';                                 \
            Code                                                    \
        }(Slice)                                                    \

namespace basecode {
    template<typename T> struct slice_t final {
        using is_static     = std::integral_constant<b8, true>; //b8=bool

        const T*            data;
        u32                 length;

        const T* end() const                    { return data + length; }
        const T* rend() const                   { return data;          }
        const T* begin() const                  { return data;          }
        const T* rbegin() const                 { return data + length; }
        const T& operator[](u32 index) const    { return data[index];   }
        operator std::string_view () const      { return std::string_view((const s8*) data, length); }
    };

    static_assert(sizeof(slice_t<u8>) <= 16, "slice_t<T> is now larger than 16 bytes!");

    namespace str {
        using slice_t = slice_t<u8>;
    }

    using line_callback_t = std::function<b8 (const str::slice_t&)>;//包装了一个参数为slice_t，返回值为b8的函数
    /*
    std::function是一个函数包装器，该函数包装器模板能包装任何类型的可调用实体，
    如普通函数，函数对象，lamda表达式等。包装器可拷贝，移动等，并且包装器类型仅仅依赖于调用特征，
    而不依赖于可调用元素自身的类型。std::function是C++11的新特性，包含在头文件<functional>中。
    一个std::function类型对象实例可以包装下列这几种可调用实体：
    函数、函数指针、成员函数、静态函数、lamda表达式和函数对象。
    std::function对象实例可被拷贝和移动，并且可以使用指定的调用特征来直接调用目标元素。
    当std::function对象实例未包含任何实际可调用实体时，
    调用该std::function对象实例将抛出std::bad_function_call异常。
    */

   // 小于号< 的重载定义
    template <typename T> inline b8 operator<(const slice_t<T>& lhs, const slice_t<T>& rhs) {
        if (&lhs == &rhs) return false;
        if (lhs.length < rhs.length) return true;
        return std::memcmp(lhs.data, rhs.data, lhs.length) < 0;
    }

   // 大于号> 的重载定义
    template <typename T> inline b8 operator>(const slice_t<T>& lhs, const slice_t<T>& rhs) {
        if (&lhs == &rhs) return false;
        if (lhs.length > rhs.length) return true;
        return std::memcmp(lhs.data, rhs.data, lhs.length) > 0;
    }

    //判断相等
    template <typename T> inline b8 operator==(const slice_t<T>& lhs, const slice_t<T>& rhs) {
        if (&lhs == &rhs) return true;
        return lhs.length == rhs.length && std::memcmp(lhs.data, rhs.data, lhs.length) == 0;
    }

    namespace slice {
        // 使用const u8指针起点，和长度，制作一个slice_t
        inline str::slice_t make(const u8* str, u32 length) { //u32 uint32_t
            return str::slice_t{.data = str, .length = length};
        }

        // 判读slice_t是否为空
        template<typename T> inline b8 empty(slice_t<T>& slice) {
            return slice.length == 0 || slice.data == nullptr;
        }

        //使用const u8指针起点，和长度，制作一个slice_t
        inline str::slice_t make(const s8* str, s32 length = -1) { //s32 int32_t
            return str::slice_t{.data = (const u8*) str, .length = length == -1 ? u32(strlen(str)) : length};
        }
    }

    namespace hash {
        template <typename T> inline u64 hash64(const slice_t<T>& key) {
            return murmur::hash64(key.data, key.length);
        }
    }
}

FORMAT_TYPE_AS(basecode::str::slice_t, std::string_view);
