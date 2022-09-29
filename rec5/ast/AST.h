#pragma once

#include "../ast/Visitor.h"

#include <memory>
#include <cstdint>
#include <utility>
#include <vector>
#include <string>


namespace ast {

    template<typename T>
    using ptr = std::unique_ptr<T>;

    struct Node {
    public:
        virtual ~Node() = default; // need a virtual destructor for polymorphism
        virtual void accept(Visitor &v) const = 0; // empty accept method.
    };

    template<typename Derived>
    struct NodeImpl : virtual Node {
    public:
        void accept(Visitor &v) const override {
            v.visit(static_cast<const Derived &>(*this));
        }
    };

    struct Statement : virtual Node {
    };

    struct Expr : virtual Node {
    };

    struct Global : Statement, NodeImpl<Global> {
        std::string _name;

        explicit Global(std::string name) : _name(std::move(name)) {}

        ~Global() override = default;
    };

// Alternatively could be a linked list
    struct Sequence : Statement, NodeImpl<Sequence> {
        std::vector<ptr<Statement>> _statements;

        explicit Sequence(std::vector<ptr<Statement>> stmts) : _statements(std::move(stmts)) {}

        ~Sequence() override = default;
    };

    struct IfElse : Statement, NodeImpl<IfElse> {
        ptr<Expr> _cond;
        ptr<Statement> _then, _else;

        IfElse(ptr<Expr> cond, ptr<Statement> then, ptr<Statement> else_)
                : _cond(std::move(cond)), _then(std::move(then)), _else(std::move(else_)) {}

        ~IfElse() override = default;
    };

    struct Assignment : Statement, NodeImpl<Assignment> {
        const std::string _name;
        ptr<Expr> _value;

        Assignment(std::string name, ptr<Expr> value)
                : _name(std::move(name)), _value(std::move(value)) {}

        ~Assignment() override = default;
    };

    struct Int final : Expr, NodeImpl<Int> {
        int32_t _value;

        explicit Int(int32_t value) : _value(value) {}

        ~Int() override = default;
    };

    struct Var final : Expr, NodeImpl<Var> {
        const std::string _name;

        explicit Var(std::string name) : _name(std::move(name)) {}

        ~Var() override = default;
    };

    struct BinOp : public Expr, NodeImpl<BinOp> {
        enum class Op {
            Add, Sub, Mul, Eq, Lt,
        };

        Op _op;
        ptr<Expr> _left, _right;

        BinOp(Op op, ptr<Expr> left, ptr<Expr> right) : _left(std::move(left)), _right(std::move(right)), _op(op) {}

        ~BinOp() override = default;
    };
}