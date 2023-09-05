#pragma once

#include "AST.h"

struct Visitor {
  virtual void visit(const Add *op) = 0;
  virtual void visit(const Int *op) = 0;
  virtual void visit(const Var *op) = 0;
};
