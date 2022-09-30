#include "Interpreter.h"
#include "../ast/AST.h"

void Interpreter::visit(const ast::Assignment &op) {

}

void Interpreter::visit(const ast::Name &op) {

}

void Interpreter::visit(const ast::FieldDereference &op) {

}

void Interpreter::visit(const ast::Int &op) {
    result = new Integer{.value=op._value};
}
