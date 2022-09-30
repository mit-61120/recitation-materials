#pragma once

#include "../util/Visitor.h"

namespace ast {
    struct Global;
    struct Sequence;
    struct Assignment;
    struct IfElse;

    struct Int;
    struct Name;
    struct FieldDereference;
    struct BinOp;

    using Visitor = util::Visitor<Global, Sequence, Assignment, IfElse, Int, Name, FieldDereference, BinOp>;

    class RecursiveVisitor : public Visitor {
    public:
        void visit(const ast::Global &op) override;
        void visit(const ast::Sequence &op) override;

        virtual void visit(const ast::Assignment &op) override;
        void visit(const ast::IfElse &op) override;

        virtual // Exprs
        void visit(const ast::Name &op) override;

        virtual void visit(const ast::FieldDereference &op) override;
        void visit(const ast::Int &op) override;
        void visit(const ast::BinOp &op) override;
    };
}