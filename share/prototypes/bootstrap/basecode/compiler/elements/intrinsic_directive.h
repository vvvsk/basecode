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

#include "directive.h"

namespace basecode::compiler {

    class intrinsic_directive : public directive {
    public:
        intrinsic_directive(
            compiler::module* module,
            compiler::block* parent_scope,
            compiler::element* expression);

    protected:
        void on_owned_elements(element_list_t& list) override;

        bool on_evaluate(compiler::session& session) override;

    private:
        compiler::element* _expression = nullptr;
    };

};

