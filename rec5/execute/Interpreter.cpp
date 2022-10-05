#include "Interpreter.h"
#include "../ast/AST.h"

void Interpreter::visit(const ast::Assignment &op) {
    op._lhs->accept(*this);
    auto writeToSaved = this->writeTo;

    op._value->accept(*this);
    writeToSaved->second = result;
}

void Interpreter::visit(const ast::Name &op) {
    if (auto it = frame.find(op._name); it != frame.end()) {
        result = it->second;
        writeTo = it;
    }
    else {
        // TODO throw
    }
}

void Interpreter::visit(const ast::FieldDereference &op) {
    op.base->accept(*this);
    auto record = static_cast<Record*>(result); // In your code, you should convert properly

    if (auto it = record->values.find(op.field->_name); it != record->values.end()) {
        result = it->second;
        writeTo = it;
    } else {
        // TODO throw
    }
}

void Interpreter::visit(const ast::Int &op) {
    result = new Integer{.value=op._value};
}
