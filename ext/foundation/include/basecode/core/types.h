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
该文件定义了项目中使用的常用数据变量的类型
*/
// ----------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <x86intrin.h>
#include <type_traits>

#if defined(WIN32)
#   define api_export   __declspec(dllexport)
#else
#   define api_export
#endif

#if defined(__GNUC__)
#   define force_inline inline __attribute__((always_inline, unused))
#   define never_inline inline __attribute__((noinline, unused))
#   ifndef likely
#       define likely(x) __builtin_expect(!!(x), 1)
#   endif
#   ifndef unlikely
#       define unlikely(x) __builtin_expect(!!(x), 0)
#   endif
#elif defined(_MSC_VER)
#   define force_inline __forceinline
#   define never_inline __declspec(noinline)
#   ifndef likely
#       define likely(x) x
#   endif
#   ifndef unlikely
#       define unlikely(x) x
#   endif
#else
#   define force_inline inline
#   define never_inline
#   ifndef likely
#       define likely(x) x
#   endif
#   ifndef unlikely
#       define unlikely(x) x
#   endif
#endif

#define ALIGNED16               __attribute__((aligned(16)))
#define UNIQUE_NAME_1(x, y)     x##y
#define UNIQUE_NAME_2(x, y)     UNIQUE_NAME_1(x, y)
#define UNIQUE_NAME_(x)         UNIQUE_NAME_2(x, __COUNTER__)
#define UNUSED(x)               ((void) x)
#define OK(x)                   (0 == (u32) x)
#define SAFE_SCOPE(x)           do { x } while (false)
#define ZERO_MEM(x, s)          std::memset((x), 0, sizeof(s))
#define HAS_ZERO(v)             (((v)-UINT64_C(0x0101010101010101)) & ~(v)&UINT64_C(0x8080808080808080))
// 定义在项目使用的数据类型
namespace basecode {
    using u0                    = void;
    using u8                    = std::uint8_t;
    using u16                   = std::uint16_t;
    //uint32_t
    using u32                   = std::uint32_t;
    using u64                   = std::uint64_t;
    using s8                    = char;
    using s16                   = std::int16_t;
    using s32                   = std::int32_t;
    using s64                   = std::int64_t;
    using b8                    = bool;
    using f32                   = float;
    using f64                   = double;
    using s128                  = __int128_t;
    using u128                  = __uint128_t;
    using usize                 = std::size_t;
    using ssize                 = ssize_t;

    struct alloc_t;

    //TODO: 弄明白union xx final 含义
    // union 表示单词使用一个union变量只会有一个生效，final 禁用了继承
    // 要么用value，要么用bytes[2]
    union u16_bytes_t final {
        u16                     value;
        u8                      bytes[2];
    };

    union u32_bytes_t final {
        u32                     value;
        u8                      bytes[4];
    };

    union u64_bytes_t final {
        u64                     value;
        u8                      bytes[8];
    };

#ifdef __SSE4_2__
    union m128i_bytes_t final {
        __m128i                 value;
        u8                      bytes[16];
    };
#endif

#ifdef __AVX2__
    union m256i_bytes_t final {
        __m256i                 value;
        u8                      bytes[32];
    };
#endif
    //TODO: concept 含义
    /*
    Concepts是用来约束模板类型的语法糖。原来，模板通过SIFNAE机制进行模板的约束匹配，这样的匹配方式，我知道的缺陷有几个：
    1. 匹配失败时报错信息难以阅读

    2. 匹配的逻辑写的实在是难以读懂，跟模板本身逻辑耦合在一起。

    3. 不同地方的匹配可能需要写很多相同模式的约束匹配的代码。
    requires关键字说明模板参数需要满足的concept，
    */

    template <typename From, typename To> concept convertible_to = std::is_convertible_v<From, To> && requires(std::add_rvalue_reference_t<From> (&f)()) {
        //C++ STL的std::is_convertible模板用于检查是否可以将任何数据类型A隐式转换为任何数据类型B。它返回布尔值true或false。
        static_cast<To>(f());
    };

    template <typename T, typename U> concept same_helper = std::is_same_v<T, U>;

    template <typename T, typename U> concept same_as = same_helper<T, U> && same_helper<U, T>;

    template <typename T> concept Slice_Concept = same_as<typename T::is_static, std::true_type> && requires(const T& t) {
        {t.data}        -> same_as<const u8*>;
        {t.length}      -> same_as<u32>;
    };

    template <typename T> concept Static_Stack_Concept = same_as<typename T::is_static, std::true_type> && requires(const T& t) {
        typename        T::value_type;
        {t.data}        -> same_as<typename T::value_type*>;
        {t.size}        -> same_as<u32>;
        {t.capacity}    -> same_as<u32>;
    };

    template <typename T> concept Dynamic_Stack_Concept = same_as<typename T::is_static, std::false_type> && requires(const T& t) {
        typename        T::value_type;
        {t.alloc}       -> same_as<alloc_t*>;
        {t.data}        -> same_as<typename T::value_type*>;
        {t.size}        -> same_as<u32>;
        {t.capacity}    -> same_as<u32>;
    };

    template <typename T> concept Static_Array_Concept = same_as<typename T::is_static, std::true_type> && requires(const T& t) {
        typename        T::value_type;
        {t.data}        -> same_as<typename T::value_type*>;
        {t.size}        -> same_as<u32>;
        {t.capacity}    -> same_as<u32>;
    };

    template <typename T> concept Dynamic_Array_Concept = same_as<typename T::is_static, std::false_type> && requires(const T& t) {
        typename        T::value_type;
        {t.alloc}       -> same_as<alloc_t*>;
        {t.data}        -> same_as<typename T::value_type*>;
        {t.size}        -> same_as<u32>;
        {t.capacity}    -> same_as<u32>;
    };

    template <typename T> concept Static_String_Concept  = same_as<typename T::is_static, std::true_type> && requires(const T& t) {
        {t.data}        -> same_as<u8*>;
        {t.length}      -> same_as<u32>;
        {t.capacity}    -> same_as<u32>;
    };

    template <typename T> concept Dynamic_String_Concept  = same_as<typename T::is_static, std::false_type> && requires(const T& t) {
        {t.alloc}       -> same_as<alloc_t*>;
        {t.data}        -> same_as<u8*>;
        {t.length}      -> same_as<u32>;
        {t.capacity}    -> same_as<u32>;
    };

    template <typename T> concept Stack_Concept     = Static_Stack_Concept<T> || Dynamic_Stack_Concept<T>;

    template <typename T> concept String_Concept    = Slice_Concept<T> || Static_String_Concept<T> || Dynamic_String_Concept<T>;

    template <typename T> concept Array_Concept     = Static_Array_Concept<T> || Dynamic_Array_Concept<T>;

    template <typename T> concept Integer_Concept   = std::is_integral_v<T>;

    template <typename T> concept Radix_Concept     = Integer_Concept<T> && requires(T radix) {
        radix == 2 || radix == 8 || radix == 10 || radix == 16;
    };

    template <typename T> concept Buffer_Concept = String_Concept<T> || requires(const T& t) {
        {t.alloc}       -> same_as<alloc_t*>;
        {t.data}        -> same_as<u8*>;
        {t.length}      -> same_as<u32>;
        {t.capacity}    -> same_as<u32>;
    };

    template <typename T> concept Status_Concept = std::is_enum_v<T> || requires(const T& t) {
        //模板接受单个参数T(特质类)，以检查T是否为枚举类型。
        typename T::ok;
    };
}
