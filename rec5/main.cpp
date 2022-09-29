#include "ast/AST.h"
#include "PrettyPrinter.h"
#include "FindGlobals.h"
#include <iostream>

template<typename T, typename ...Args>
auto make(Args &&...args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

int main(int argc, char *argv[]) {
    using namespace ast;
    auto a_plus_one = make<BinOp>(BinOp::Op::Add, make<Var>("a"), make<Int>(1));
    auto b = make<BinOp>(BinOp::Op::Mul, std::move(a_plus_one), make<Int>(1));

    ptr<Statement> statements[]{
            make<Global>("x"),
            make<Assignment>("a", make<Int>(1)),
            make<IfElse>(
                    make<BinOp>(BinOp::Op::Eq, make<Var>("a"), make<Int>(4)),
                    make<Assignment>("a", make<BinOp>(
                            BinOp::Op::Sub, make<Int>(3), std::move(b))
                    ),
                    make<Global>("a")
            )
    };

    auto body = make<Sequence>(std::vector<ptr<Statement>>(
            std::make_move_iterator(std::begin(statements)),
            std::make_move_iterator(std::end(statements)))
    );

    PrettyPrinter p(std::cout);
    body->accept(p);
    std::cout << std::endl;

    FindGlobals fg;
    body->accept(fg);

    for (const auto &g: fg.globals) {
        std::cout << "found global: " << g << "\n";
    }

    return 0;
}
