// ----------------------------------------------------------------------------
//
// Basecode Bootstrap Compiler
// Copyright (C) 2018 Jeff Panici
// All rights reserved.
//
// This software source file is licensed under the terms of MIT license.
// For details, please read the LICENSE file.
//
// ----------------------------------------------------------------------------

#pragma once

#include "element.h"

namespace basecode::compiler {

    class fallthrough : public element {
    public:
        fallthrough(
            compiler::module* module,
            compiler::block* parent_scope,
            compiler::label* label);

        compiler::label* label();

    protected:
        void on_owned_elements(element_list_t& list) override;

    private:
        compiler::label* _label = nullptr;
    };

};

