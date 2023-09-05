#include "Interpreter.h"

#include "../ast/AST.h"

void Interpreter::visit(const ast::Assignment &op) {
  // option 1
  auto writeTo = lValueResolver.resolve(*op._lhs);
  op._value->accept(*this);
  writeTo.write(result);
}

void Interpreter::visit(const ast::Name &op) {
  if (auto it = frame.find(op._name); it != frame.end()) {
    result = it->second;
  } else {
    throw std::runtime_error("variable not found");
  }
}

void Interpreter::visit(const ast::FieldDereference &op) {
  op.base->accept(*this);
  auto record = static_cast<Record *>(
      result);  // In your code, you should convert properly

  if (auto it = record->values.find(op.field->_name);
      it != record->values.end()) {
    result = it->second;
  } else {
    throw std::runtime_error("field not found");
  }
}

void Interpreter::visit(const ast::Int &op) {
  result = new Integer{.value = op._value};
}

void Interpreter::visit(const ast::Record &op) {
  auto record = new Record{};
  for (auto &&field : op._fields) {
    field.second->accept(*this);
    record->values[field.first] = result;
  }
  result = record;
}
