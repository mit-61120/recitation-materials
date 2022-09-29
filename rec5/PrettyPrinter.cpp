#include "PrettyPrinter.h"
#include "ast/AST.h"

void PrettyPrinter::print_indent() {
    stream << std::string(indent, ' ');
}

void PrettyPrinter::visit(const ast::Global &op) {
    // Nothing to recurse on.
    print_indent();
    stream << "global " << op._name << ";\n";
}

void PrettyPrinter::visit(const ast::IfElse &op) {
    print_indent();
    stream << "if (";
    op._cond->accept(*this);
    stream << ") {\n";
    indent++;
    op._then->accept(*this);
    indent--;
    print_indent();
    stream << "}";
    if (op._else) {
        stream << " else {\n";
        indent++;
        op._else->accept(*this);
        indent--;
        print_indent();
        stream << "}";
    }
    stream << "\n";
}

void PrettyPrinter::visit(const ast::Assignment &op) {
    print_indent();
    stream << op._name << " = ";
    op._value->accept(*this);
    stream << ";\n";
}

void PrettyPrinter::visit(const ast::Int &op) {
    stream << op._value;
}

void PrettyPrinter::visit(const ast::Var &op) {
    stream << op._name;
}

void PrettyPrinter::visit(const ast::BinOp &op) {
    stream << "(";
    op._left->accept(*this);
    switch(op._op) {
        using Op = ast::BinOp::Op;
        case Op::Add: {
            stream << " + ";
            break;
        }
        case Op::Sub: {
            stream << " - ";
            break;
        }
        case Op::Mul: {
            stream << " * ";
            break;
        }
        case Op::Eq: {
            stream << " == ";
            break;
        }
        case Op::Lt: {
            stream << " < ";
            break;
        }
    }
    op._right->accept(*this); // this is a Visitor *
    stream << ")";
}
