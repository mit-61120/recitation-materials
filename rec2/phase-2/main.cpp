#include <cassert>
#include <iostream>
#include <map>

#include "ast/AST.h"
#include "ast/Visitor.h"

struct Value {
  enum class Type { INT, BOOL };
  Type type;

  virtual int32_t getInt() { return 0; }

  virtual bool getBool() { return false; }

  virtual std::string toString() { return "ERROR"; }

  Value(Type _type) : type(_type) {}
};

struct Integer : public Value {
  int32_t value = 0;

  int32_t getInt() override { return value; }

  std::string toString() override { return std::to_string(value); }

  Integer(int32_t _value) : value(_value), Value(Value::Type::INT) {}
};

struct Boolean : public Value {
  bool value = false;

  bool getBool() override { return value; }

  std::string toString() override { return value ? "true" : "false"; }

  Boolean(bool _value) : value(_value), Value(Value::Type::BOOL) {}
};

class Interpreter : public ast::EmptyVisitor {
 public:
  void visit(const ast::Block &ir) override {
    for (auto &&stmt : ir.statements) {
      stmt->accept(*this);
    }
  }

  // Stmts
  void visit(const ast::Assignment &ir) override {
    const std::string &name =
        static_cast<ast::Name *>(ir.lhs.get())
            ->name;  // bad code, what if LHS is not a Name?
    ir.expression->accept(*this);
    frame[name] = rval;
  }

  // Exprs
  void visit(const ast::BinaryExpr &ir) override {
    ir.left->accept(*this);
    Value *left = rval;

    ir.right->accept(*this);
    Value *right = rval;

    // your code should do type checking somewhere!!
    using BinaryOp = ast::BinaryExpr::Operator;

    switch (ir.op) {
      case BinaryOp::PLUS: {
        rval = new Integer(left->getInt() + right->getInt());
        return;
      }
      case BinaryOp::MUL: {
        rval = new Integer(left->getInt() * right->getInt());
        return;
      }
      case BinaryOp::DIV: {
        // you should check for riht->getInt() == 0 case.
        rval = new Integer(left->getInt() / right->getInt());
        return;
      }
      case BinaryOp::LT: {
        rval = new Boolean(left->getInt() < right->getInt());
        return;
      }
      default: {
        rval = nullptr;
        assert(false);
      }
    }
  }

  void visit(const ast::UnaryExpr &ir) override {
    ir.expr->accept(*this);
    // rval should store the value we want

    using UnaryOp = ast::UnaryExpr::Operator;

    switch (ir.op) {
      case UnaryOp::NOT: {
        rval = new Boolean(!rval->getBool());
        return;
      }
      case UnaryOp::MINUS: {
        rval = new Integer(-rval->getInt());
        return;
      }
    }
  }

  void visit(const ast::Name &ir) override { rval = frame[ir.name]; }

  void visit(const ast::IntConstant &ir) override {
    rval = new Integer(ir.value);
  }

  void print() {
    for (auto &value : frame) {
      std::cout << value.first << " : " << value.second->toString() << "\n";
    }
  }

 private:
  Value *rval = nullptr;
  std::map<std::string, Value *> frame;
};

int main(int argc, const char *argv[]) {
  // x = 5 + 20 /-(2);
  auto assignment = std::make_unique<ast::Assignment>(
      std::make_unique<ast::Name>("x"),
      std::make_unique<ast::BinaryExpr>(
          ast::BinaryExpr::Operator::PLUS,
          std::make_unique<ast::IntConstant>(5),
          std::make_unique<ast::BinaryExpr>(
              ast::BinaryExpr::Operator::DIV,
              std::make_unique<ast::IntConstant>(20),
              std::make_unique<ast::UnaryExpr>(
                  ast::UnaryExpr::Operator::MINUS,
                  std::make_unique<ast::IntConstant>(2)))));

  Interpreter interp;
  assignment->accept(interp);
  interp.print();

  return 0;
}
