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

#include "type.h"

namespace basecode::compiler {

    class pointer_type : public compiler::type {
    public:
        static std::string name_for_pointer(compiler::type* base_type);

        pointer_type(
            compiler::module* module,
            compiler::block* parent_scope,
            compiler::type_reference* base_type);

        bool is_pointer_type() const override;

        bool is_unknown_type() const override;

        bool is_composite_type() const override;

        compiler::type_reference* base_type_ref() const;

        void base_type_ref(compiler::type_reference* value);

        std::string name(const std::string& alias = "") const override;

    protected:
        bool on_type_check(compiler::type* other) override;

        number_class_t on_number_class() const override;

        bool on_initialize(compiler::session& session) override;

    private:
        compiler::type_reference* _base_type_ref = nullptr;
    };

};

