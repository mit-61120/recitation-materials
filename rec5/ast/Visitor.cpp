#include "AST.h"
#include "Visitor.h"

void ast::RecursiveVisitor::visit(const ast::Global &op) {

}

void ast::RecursiveVisitor::visit(const ast::Sequence &op) {
    for (auto &&statement: op._statements) {
        statement->accept(*this);
    }
}

void ast::RecursiveVisitor::visit(const ast::Assignment &op) {
    op._value->accept(*this);
}

void ast::RecursiveVisitor::visit(const ast::IfElse &op) {
    op._cond->accept(*this);
    op._then->accept(*this);
    if (op._else) {
        op._else->accept(*this);
    }
}

void ast::RecursiveVisitor::visit(const ast::Var &op) {

}

void ast::RecursiveVisitor::visit(const ast::Int &op) {

}

void ast::RecursiveVisitor::visit(const ast::BinOp &op) {

}
