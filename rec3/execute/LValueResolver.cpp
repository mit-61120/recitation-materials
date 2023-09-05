//
// Created by Luka on 10/7/2022.
//

#include "LValueResolver.h"

#include "../ast/AST.h"
#include "Interpreter.h"

void LValueResolver::visit(const ast::Name &op) {
  lValue = {interpreter.frame, op._name};  // actual lookup
}

LValueResolver::LValueResolver(Interpreter &interpreter)
    : interpreter(interpreter) {}

LValueResolver::LValue LValueResolver::resolve(const ast::LHS &lhs) {
  lhs.accept(*this);
  return lValue;
}

void LValueResolver::visit(const ast::FieldDereference &node) {
  node.base->accept(interpreter);
  auto record = static_cast<Record *>(
      interpreter.result);  // In your code, you should convert properly

  lValue = {record->values, node.field->_name};
}
