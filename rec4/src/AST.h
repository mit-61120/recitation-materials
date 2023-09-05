#pragma once

#include <memory>
#include <cstdint>
#include <vector>

struct SystemException {
	  std::string msg_;
	  SystemException(const std::string& msg) :msg_(msg) {}
};

struct Visitor;

struct Stmt {
    virtual ~Stmt() = default; // do nothing destructor
    virtual void accept(Visitor *v) const = 0; // empty accept method.
};

typedef std::shared_ptr<Stmt> StmtPtr;

struct Expr {
    virtual ~Expr() = default; // do nothing destructor
    virtual void accept(Visitor *v) const = 0; // empty accept method.
};

typedef std::shared_ptr<Expr> ExprPtr;

// Alternatively could be a linked list
struct Block : public Stmt {
    std::vector<StmtPtr> _stmts;

    Block(const std::vector<StmtPtr> &stmts) : _stmts(stmts) {}
    virtual ~Block() = default;
    virtual void accept(Visitor *v) const override;

    static std::shared_ptr<Block> make(const std::vector<StmtPtr> &stmts);
    static std::shared_ptr<Block> make();

    void AddStmt(StmtPtr stmt);
};

// This is essentially the same as Block.
struct Program final : public Block {
    ~Program() = default;
    Program(const std::vector<StmtPtr> &stmts) : Block(stmts) {}
    static std::shared_ptr<Program> make();
};

struct If final : public Stmt {
    ExprPtr _cond;
    StmtPtr _then;

    If(const ExprPtr &cond, const StmtPtr &then)
      : _cond(cond), _then(then) {}
    virtual ~If() = default;
    virtual void accept(Visitor *v) const override;

    static std::shared_ptr<If> make(const ExprPtr &_cond, const StmtPtr &_then);
};

struct Var;

struct Assignment final : public Stmt {
    std::shared_ptr<Var> _lhs;
    ExprPtr _value;

    Assignment(std::shared_ptr<Var> lhs, const ExprPtr &value)
      : _lhs(std::move(lhs)), _value(value) {}

    virtual ~Assignment() = default;
    virtual void accept(Visitor *v) const override;

    static std::shared_ptr<Assignment> make(std::shared_ptr<Var> lhs, const ExprPtr &value);
};

struct Int final : public Expr {
    int32_t _value;

    ~Int() = default;
    Int(int32_t value) : _value(value) {}
    void accept(Visitor *v) const override;

    static std::shared_ptr<Int> make(int32_t value);
};

struct Bool final : public Expr {
    bool _value;

    ~Bool() = default;
    Bool(bool value) : _value(value) {}
    void accept(Visitor *v) const override;

    static std::shared_ptr<Bool> make(bool value);
};

struct Var final : public Expr {
    const std::string _name;

    ~Var() = default;
    Var(const std::string &name) : _name(name) {}
    void accept(Visitor *v) const override;
    
    static std::shared_ptr<Var> make(const std::string &name);
};

struct BinOp final : public Expr {
    enum Op {
        Add, Sub, Mul, Eq, Lt,
        Error, // this is for error handling
    };

    Op _op;
    ExprPtr _a, _b;

    BinOp(Op op, const ExprPtr &a, const ExprPtr &b) : _a(a), _b(b), _op(op) {}
    void accept(Visitor *v) const override;

    static std::shared_ptr<BinOp> make(Op op, const ExprPtr &a, const ExprPtr &b);
};
