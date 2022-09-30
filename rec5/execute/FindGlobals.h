#pragma once

#include "../ast/Visitor.h"

#include <iostream>
#include <string>
#include <set>

struct FindGlobals final : public ast::RecursiveVisitor {
    void visit(const ast::Global &op) override;

    std::set<std::string> globals;
};
