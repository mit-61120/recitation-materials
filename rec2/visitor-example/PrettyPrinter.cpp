#include "PrettyPrinter.h"

void PrettyPrinter::visit(const Add *op) {
  stream << "(";
  op->a->accept(this);  // this is a Visitor *
  stream << " + ";
  op->b->accept(this);  // this is a Visitor *
  stream << ")";
}

void PrettyPrinter::visit(const Int *op) { stream << op->value; }

void PrettyPrinter::visit(const Var *op) { stream << op->name; }
