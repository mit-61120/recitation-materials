#include "Visitor.h"

void Visitor::visit(const Block *op) {
  for (const auto &stmt : op->_stmts) {
    stmt->accept(this);
  }
}

void Visitor::visit(const If *op) {
  op->_cond->accept(this);
  op->_then->accept(this);
}

void Visitor::visit(const Assignment *op) { op->_value->accept(this); }

void Visitor::visit(const Int *op) {
  // Nothing to recurse on.
}

void Visitor::visit(const Bool *op) {
  // Nothing to recurse on.
}

void Visitor::visit(const Var *op) {
  // Nothing to recurse on.
}

void Visitor::visit(const BinOp *op) {
  op->_a->accept(this);
  op->_b->accept(this);
}
