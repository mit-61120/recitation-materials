#include "Interpreter.h"
#include "../ast/AST.h"

void Interpreter::visit(const ast::Assignment &op) {
    // option 1
    auto writeTo = lValueResolver.resolve(*op._lhs);
    op._value->accept(*this);
    writeTo.write(result);

    // option 2:
    if(auto name = dynamic_cast<ast::Name*>(op._lhs.get()); name) {
        op._value->accept(*this);
        frame[name->_name] = result;
    } else if(auto field = dynamic_cast<ast::FieldDereference*>(op._lhs.get()); field) {
        field->base->accept(*this);
        auto record = static_cast<Record*>(result); // In your code, you should convert properly
        op._value->accept(*this);

        record->values[field->field->_name] = result;
    } else if(false){
        // TODO IndexExpression
    } else {
        // TODO throw
    }
}

void Interpreter::visit(const ast::Name &op) {
    if (auto it = frame.find(op._name); it != frame.end()) {
        result = it->second;
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
    } else {
        // TODO throw
    }
}

void Interpreter::visit(const ast::Int &op) {
    result = new Integer{.value=op._value};
}
