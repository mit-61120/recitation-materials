#pragma once

#include <iostream>
#include <set>
#include <string>

#include "../ast/Visitor.h"

struct FindGlobals final : public ast::RecursiveVisitor {
  void visit(const ast::Global &op) override;

  std::set<std::string> globals;
};
