#include <iostream>

#include "PrettyPrinter.h"
#include "ast/AST.h"
#include "execute/FindGlobals.h"
#include "execute/Interpreter.h"

template <typename T, typename... Args>
auto make(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

int main(int argc, char *argv[]) {
  using namespace ast;
  auto a_plus_one = make<BinOp>(BinOp::Op::Add, make<Name>("a"), make<Int>(1));
  auto b = make<BinOp>(BinOp::Op::Mul, std::move(a_plus_one), make<Int>(1));
  std::map<std::string, ptr<Expr>> args;
  args.emplace("size", make<Int>(10));
  args.emplace("data", make<Name>("a"));

  ptr<Statement> statements[]{
      make<Global>(make<Name>("x")),
      make<Assignment>(make<Name>("a"), make<Int>(1)),
      make<Assignment>(make<Name>("y"), make<ast::Record>(std::move(args))),
      make<Assignment>(
          make<FieldDereference>(make<Name>("y"), make<Name>("size")),
          make<Int>(1)),
      make<IfElse>(make<BinOp>(BinOp::Op::Eq, make<Name>("a"), make<Int>(4)),
                   make<Assignment>(
                       make<Name>("a"),
                       make<BinOp>(BinOp::Op::Sub, make<Int>(3), std::move(b))),
                   make<Global>(make<Name>("a")))};

  auto body = make<Sequence>(std::vector<ptr<Statement>>(
      std::make_move_iterator(std::begin(statements)),
      std::make_move_iterator(std::end(statements))));

  PrettyPrinter p(std::cout);
  body->accept(p);
  std::cout << std::endl;

  FindGlobals fg;
  body->accept(fg);

  for (const auto &g : fg.globals) {
    std::cout << "found global: " << g << "\n";
  }

  Interpreter interpreter;
  std::cout << "Interpreting..." << std::endl;
  body->accept(interpreter);
  return 0;
}
