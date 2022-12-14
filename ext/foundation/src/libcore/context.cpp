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
// ----------------------------------------------------------------------------

#include <cassert>
#include <basecode/core/context.h>

namespace basecode::context {
    static constexpr u32        stack_size = 512; //站的大小

    thread_local u32            t_index = stack_size; //有且只有 thread_local 关键字修饰的变量具有线程（thread）周期，
    //这些变量在线程开始的时候被生成，在线程结束的时候被销毁，并且每一个线程都拥有一个独立的变量实例
    thread_local context_t*     t_stack[stack_size]; // 定义一个长度为512的数组，存放context指针

    u0 pop() {
        assert(t_index < stack_size);
        t_index++;
    }

    
    context_t* top() {
        assert(t_index < stack_size);
        return t_stack[t_index];
    }

    u0 push(context_t* ctx) {
        assert(t_index > 0);
        t_stack[--t_index] = ctx;
    }
    // 使用参数建立一个context
    context_t make(s32 argc, const s8** argv, alloc_t* alloc, logger_t* logger) {
        context_t ctx{};
        ctx.user   = {};
        ctx.argc   = argc;
        ctx.argv   = argv;
        ctx.alloc  = alloc;
        ctx.logger = logger;
        return ctx;
    }
}
