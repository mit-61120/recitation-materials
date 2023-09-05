#pragma once

#include "AST.h"

struct Visitor {
    // Stmts
    virtual void visit(const Block *op);
    virtual void visit(const If *op);
    virtual void visit(const Assignment *op);

    // Exprs
    virtual void visit(const Int *op);
    virtual void visit(const Bool *op);
    virtual void visit(const Var *op);
    virtual void visit(const BinOp *op);
};
