#include "Interpreter.h"
#include "../ast/AST.h"

void Interpreter::visit(const ast::Assignment &op) {
    write = true;
    op._lhs->accept(*this);
    write = false;
    op._value->accept(*this);
    writeTo->second = result;
}

void Interpreter::visit(const ast::Name &op) {
    if (auto it = frame.find(op._name); it != frame.end()) {
        result = it->second;
        if(write) writeTo = it;
    }
    else {
        // TODO throw
    }
}

void Interpreter::visit(const ast::FieldDereference &op) {
    op.base->accept(*this);
    auto record = static_cast<Record*>(result);

    if (auto it = record->values.find(op.field->_name); it != record->values.end()) {
        result = it->second;
        if(write) writeTo = it;
    } else {
        // TODO throw
    }
}

void Interpreter::visit(const ast::Int &op) {
    result = new Integer{.value=op._value};
}
