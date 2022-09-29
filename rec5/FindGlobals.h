#pragma once

#include <iostream>
#include <string>
#include <set>

#include "ast/Visitor.h"

struct FindGlobals final : public ast::RecursiveVisitor {
    void visit(const ast::Global &op) override;

    std::set<std::string> globals;
};
