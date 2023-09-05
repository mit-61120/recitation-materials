#include "AST.h"
#include "Visitor.h"
#include <memory>

void Block::accept(Visitor *v) const {
    v->visit(this);
}

std::shared_ptr<Block> Block::make(const std::vector<StmtPtr> &stmts) {
    return std::make_shared<Block>(stmts);
}

std::shared_ptr<Block> Block::make() {
    const std::vector<StmtPtr> empty;
    return std::make_shared<Block>(empty);
}

void Block::AddStmt(StmtPtr stmt) {
    _stmts.emplace_back(std::move(stmt));
}

std::shared_ptr<Program> Program::make() {
    const std::vector<StmtPtr> empty;
    return std::make_shared<Program>(empty);
}


void If::accept(Visitor *v) const {
    v->visit(this);
}

std::shared_ptr<If> If::make(const ExprPtr &_cond, const StmtPtr &_then) {
    return std::make_shared<If>(_cond, _then);
}


void Assignment::accept(Visitor *v) const {
    v->visit(this);
}

std::shared_ptr<Assignment> Assignment::make(std::shared_ptr<Var> lhs, const ExprPtr &value) {
    return std::make_shared<Assignment>(std::move(lhs), value);
}


void Int::accept(Visitor *v) const {
    v->visit(this);
}

std::shared_ptr<Int> Int::make(int32_t value) {
    return std::make_shared<Int>(value);
}


void Bool::accept(Visitor *v) const {
    v->visit(this);
}

std::shared_ptr<Bool> Bool::make(bool value) {
    return std::make_shared<Bool>(value);
}


void Var::accept(Visitor *v) const {
    v->visit(this);
}

std::shared_ptr<Var> Var::make(const std::string &name) {
    return std::make_shared<Var>(name);
}


void BinOp::accept(Visitor *v) const {
    v->visit(this);
}

std::shared_ptr<BinOp> BinOp::make(Op op, const ExprPtr &a, const ExprPtr &b) {
    return std::make_shared<BinOp>(op, a, b);
}
