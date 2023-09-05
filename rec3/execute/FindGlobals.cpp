#include "FindGlobals.h"

#include "../ast/AST.h"

void FindGlobals::visit(const ast::Global &op) {
  globals.insert(op._name->_name);
}
