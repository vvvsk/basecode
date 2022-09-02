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
#include <compiler/scope_manager.h>
#include "type.h"
#include "numeric_type.h"
#include "float_literal.h"

namespace basecode::compiler {

    float_literal::float_literal(
            compiler::module* module,
            block* parent_scope,
            double value) : element(module, parent_scope, element_type_t::float_literal),
                            _value(value) {
    }

    bool float_literal::on_infer_type(
            compiler::session& session,
            infer_type_result_t& result) {
        result.inferred_type = session
            .scope_manager()
            .find_type(qualified_symbol_t(numeric_type::narrow_to_value(_value)));
        return true;
    }

    double float_literal::value() const {
        return _value;
    }

    bool float_literal::is_signed() const {
        return _value < 0;
    }

    bool float_literal::on_is_constant() const {
        return true;
    }

    bool float_literal::on_as_float(double& value) const {
        value = _value;
        return true;
    }

};