#pragma once

#include <functional>
#include <map>
#include <string>
#include <utility>

#include "../ast/Visitor.h"

class Interpreter;

class Value;
namespace ast {
class LHS;
}

class LValueResolver : public ast::RecursiveVisitor {
 public:
  struct LValue {
    std::reference_wrapper<std::map<std::string, Value *>> dest;
    std::string key;

    void write(Value *value) const { dest.get()[key] = value; }
  };

  explicit LValueResolver(Interpreter &interpreter);

  [[nodiscard]] LValue resolve(const ast::LHS &lhs);

  void visit(const ast::Name &op) override;

  void visit(const ast::FieldDereference &op) override;

 private:
  Interpreter &interpreter;

  std::map<std::string, Value *> dummy;
  LValue lValue{dummy, ""};
};
