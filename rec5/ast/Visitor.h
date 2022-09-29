#pragma once

#include "../util/Visitor.h"

namespace ast {
    struct Global;
    struct Sequence;
    struct Assignment;
    struct IfElse;

    struct Int;
    struct Var;
    struct BinOp;

    using Visitor = util::Visitor<Global, Sequence, Assignment, IfElse, Int, Var, BinOp>;

    class RecursiveVisitor : public Visitor {
    public:
        void visit(const ast::Global &op) override;
        void visit(const ast::Sequence &op) override;
        void visit(const ast::Assignment &op) override;
        void visit(const ast::IfElse &op) override;

        // Exprs
        void visit(const ast::Var &op) override;
        void visit(const ast::Int &op) override;
        void visit(const ast::BinOp &op) override;
    };
}