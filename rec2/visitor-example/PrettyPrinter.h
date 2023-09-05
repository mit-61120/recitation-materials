#pragma once

#include <iostream>
#include "Visitor.h"

struct PrettyPrinter final : public Visitor {
    PrettyPrinter(std::ostream &_stream) : stream(_stream) {}
    std::ostream &stream;

    void visit(const Add *op) override;
    void visit(const Int *op) override;
    void visit(const Var *op) override;
};
