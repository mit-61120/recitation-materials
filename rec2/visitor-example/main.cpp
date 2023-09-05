#include <iostream>

#include "AST.h"
#include "PrettyPrinter.h"

int main(int argc, char *argv[]) {
  ExprPtr a = std::make_shared<Var>("a");
  ExprPtr one = std::make_shared<Int>(1);
  ExprPtr a_plus_one = std::make_shared<Add>(a, one);

  std::cout << a_plus_one << std::endl;

  PrettyPrinter p(std::cout);
  a_plus_one->accept(&p);
  std::cout << std::endl;

  return 0;
}
