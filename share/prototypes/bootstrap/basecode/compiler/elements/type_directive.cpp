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

#include <compiler/session.h>
#include "type_directive.h"

namespace basecode::compiler {

    type_directive::type_directive(
            compiler::module* module,
            compiler::block* parent_scope,
            compiler::element* expression) : directive(module, parent_scope, "type"),
                                             _expression(expression) {
    }

    bool type_directive::on_infer_type(
            compiler::session& session,
            infer_type_result_t& result) {
        if (_expression == nullptr)
            return false;
        return _expression->infer_type(session, result);
    }

    bool type_directive::on_is_constant() const {
        return _expression != nullptr
            && _expression->element_type() == element_type_t::type_reference;
    }

    void type_directive::on_owned_elements(element_list_t& list) {
        list.emplace_back(_expression);
    }

};