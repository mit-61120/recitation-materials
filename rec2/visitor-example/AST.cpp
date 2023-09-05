#include "AST.h"

#include "Visitor.h"

void Add::accept(Visitor *v) const {
  v->visit(this);  // this is a const Add *
}

void Int::accept(Visitor *v) const {
  v->visit(this);  // this is a const Int *
}

void Var::accept(Visitor *v) const {
  v->visit(this);  // this is a const Var *
}
