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

    class statement : public element {
    public:
        statement(
            compiler::module* module,
            compiler::block* parent_scope,
            compiler::element* expr);

        label_list_t& labels();

        compiler::element* expression();

        void expression(compiler::element* value);

    protected:
        bool on_apply_fold_result(
            compiler::element* e,
            const fold_result_t& fold_result) override;

        void on_owned_elements(element_list_t& list) override;

    private:
        label_list_t _labels {};
        compiler::element* _expression = nullptr;
    };

};

