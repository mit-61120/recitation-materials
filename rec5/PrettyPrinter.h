#pragma once

#include "ast/Visitor.h"
#include "ast/AST.h"

#include <iostream>
#include <string>

struct PrettyPrinter final : public ast::RecursiveVisitor {
    explicit PrettyPrinter(std::ostream &_stream) : stream(_stream) {}

    std::ostream &stream;
    size_t indent = 0;

    void visit(const ast::Global &op) final;
    void visit(const ast::Assignment &op) final;
    void visit(const ast::IfElse &op) final;

    // Exprs
    void visit(const ast::Name &op) final;
    void visit(const ast::FieldDereference &op) final;
    void visit(const ast::Int &op) final;
    void visit(const ast::BinOp &op) final;

private:
    void print_indent();
};
