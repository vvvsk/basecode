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

#include <compiler/compiler_types.h>

namespace basecode::compiler {

    class element {
    public:
        element(
            compiler::module* module,
            block* parent_scope,
            element_type_t type,
            element* parent_element = nullptr);

        virtual ~element() = default;

        bool fold(
            compiler::session& session,
            fold_result_t& result);

        bool infer_type(
            compiler::session& session,
            infer_type_result_t& result);

        bool is_type() const;

        void make_non_owning();

        bool apply_fold_result(
            compiler::element* e,
            const fold_result_t& fold_result);

        common::id_t id() const;

        template <typename T>
        T* parent_element_as() {
            if (_parent_element == nullptr)
                return nullptr;
            return dynamic_cast<T*>(_parent_element);
        }

        bool non_owning() const;

        bool is_constant() const;

        element* parent_element();

        compiler::module* module();

        comment_list_t& comments();

        block* parent_scope() const;

        attribute_map_t& attributes();

        bool as_bool(bool& value) const;

        virtual bool is_singleton() const;

        bool as_float(double& value) const;

        element_type_t element_type() const;

        void parent_element(element* value);

        bool is_pointer_dereference() const;

        void module(compiler::module* value);

        virtual std::string label_name() const;

        bool as_integer(uint64_t& value) const;

        bool as_string(std::string& value) const;

        bool as_rune(common::rune_t& value) const;

        void owned_elements(element_list_t& list);

        bool operator> (const element& other) const {
            return on_greater_than(other);
        }

        bool operator< (const element& other) const {
            return on_less_than(other);
        }

        bool operator== (const element& other) const {
            return on_equals(other);
        }

        bool operator!= (const element& other) const {
            return on_not_equals(other);
        }

        bool operator>= (const element& other) const {
            return on_greater_than_or_equal(other);
        }

        bool operator<= (const element& other) const {
            return on_less_than_or_equal(other);
        }

        const common::source_location& location() const;

        uint64_t operator+ (const element& other) const {
            return on_add(other);
        }

        uint64_t operator- (const element& other) const {
            return on_subtract(other);
        }

        uint64_t operator* (const element& other) const {
            return on_multiply(other);
        }

        attribute* find_attribute(const std::string& name);

        bool is_directive_named(const std::string& name) const;

        void location(const common::source_location& location);

        bool as_identifier(compiler::identifier*& value) const;

        bool is_type_one_of(const element_type_set_t& types) const;

        bool is_parent_type_one_of(const element_type_set_t& types) const;

    protected:
        virtual bool on_fold(
            compiler::session& session,
            fold_result_t& result);

        virtual bool on_infer_type(
            compiler::session& session,
            infer_type_result_t& result);

        virtual bool on_apply_fold_result(
            compiler::element* e,
            const fold_result_t& fold_result);

        virtual bool on_is_constant() const;

        virtual bool on_as_bool(bool& value) const;

        virtual bool on_as_float(double& value) const;

        virtual bool on_as_integer(uint64_t& value) const;

        virtual bool on_equals(const element& other) const;

        virtual bool on_as_string(std::string& value) const;

        virtual uint64_t on_add(const element& other) const;

        virtual void on_owned_elements(element_list_t& list);

        virtual bool on_as_rune(common::rune_t& value) const;

        virtual bool on_less_than(const element& other) const;

        virtual bool on_not_equals(const element& other) const;

        virtual uint64_t on_subtract(const element& other) const;

        virtual uint64_t on_multiply(const element& other) const;

        virtual bool on_greater_than(const element& other) const;

        virtual bool on_less_than_or_equal(const element& other) const;

        virtual bool on_greater_than_or_equal(const element& other) const;

        virtual bool on_as_identifier(compiler::identifier*& value) const;

    private:
        common::id_t _id;
        bool _non_owning = false;
        comment_list_t _comments {};
        block* _parent_scope = nullptr;
        attribute_map_t _attributes {};
        element* _parent_element = nullptr;
        compiler::module* _module = nullptr;
        common::source_location _location {};
        element_type_t _element_type = element_type_t::element;
    };

};

