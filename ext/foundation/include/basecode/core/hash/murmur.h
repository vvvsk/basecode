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
该文件定义了需要用到的hash 函数
*/
// ----------------------------------------------------------------------------

#pragma once

#include <basecode/core/types.h>

namespace basecode::hash::murmur {
    u32 hash32(const u0* src, usize len);

    u64 hash64(const u0* src, usize len);

    u32 hash32(const u0* src, usize len, u32 seed);

    u64 hash64(const u0* src, usize len, u64 seed);
}
