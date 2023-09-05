#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../ast/Visitor.h"

namespace ast {

template <typename T>
using ptr = std::unique_ptr<T>;

struct Node {
 public:
  virtual ~Node() = default;  // need a virtual destructor for polymorphism
  virtual void accept(Visitor &v) const = 0;  // empty accept method.
};

template <typename Derived>
struct NodeImpl : virtual Node {
 public:
  void accept(Visitor &v) const override {
    v.visit(static_cast<const Derived &>(*this));
  }
};

struct Statement : virtual Node {};

struct Expr : virtual Node {};

struct LHS : Expr {};

struct Name : LHS, NodeImpl<Name> {
  std::string _name;

  explicit Name(std::string name) : _name(std::move(name)) {}
};

struct FieldDereference : LHS, NodeImpl<FieldDereference> {
  ptr<LHS> base;
  ptr<Name> field;

  FieldDereference(ptr<ast::LHS> base, ptr<Name> field)
      : base(std::move(base)), field(std::move(field)) {}
};

struct Global : Statement, NodeImpl<Global> {
  ptr<Name> _name;

  explicit Global(ptr<Name> name) : _name(std::move(name)) {}
};

struct Sequence : Statement, NodeImpl<Sequence> {
  // Alternatively could be a linked list
  std::vector<ptr<Statement>> _statements;

  explicit Sequence(std::vector<ptr<Statement>> stmts)
      : _statements(std::move(stmts)) {}
};

struct IfElse : Statement, NodeImpl<IfElse> {
  ptr<Expr> _cond;
  ptr<Statement> _then, _else;

  IfElse(ptr<Expr> cond, ptr<Statement> then, ptr<Statement> else_)
      : _cond(std::move(cond)),
        _then(std::move(then)),
        _else(std::move(else_)) {}
};

struct Assignment : Statement, NodeImpl<Assignment> {
  ptr<LHS> _lhs;
  ptr<Expr> _value;

  Assignment(ptr<LHS> lhs, ptr<Expr> value)
      : _lhs(std::move(lhs)), _value(std::move(value)) {}
};

struct Int final : Expr, NodeImpl<Int> {
  int32_t _value;

  explicit Int(int32_t value) : _value(value) {}
};

struct BinOp : public Expr, NodeImpl<BinOp> {
  enum class Op {
    Add,
    Sub,
    Mul,
    Eq,
    Lt,
  };

  Op _op;
  ptr<Expr> _left, _right;

  BinOp(Op op, ptr<Expr> left, ptr<Expr> right)
      : _left(std::move(left)), _right(std::move(right)), _op(op) {}
};

struct Record : public Expr, NodeImpl<Record> {
  std::map<std::string, ptr<Expr>> _fields;

  explicit Record(std::map<std::string, ptr<Expr>> fields)
      : _fields(std::move(fields)) {}
};
}  // namespace ast
