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

    class foreign_directive : public directive {
    public:
        foreign_directive(
            compiler::module* module,
            compiler::block* parent_scope,
            compiler::element* expression);

    protected:
        void on_owned_elements(element_list_t& list) override;

        bool on_evaluate(compiler::session& session) override;

    private:
        bool apply_assignment(
            compiler::session& session,
            const std::string& library_name,
            compiler::assignment* assignment);

        bool apply_directive(
            compiler::session& session,
            const std::string& library_name,
            compiler::identifier* identifier,
            compiler::procedure_type* proc_type);

    private:
        compiler::element* _expression = nullptr;
    };

};

