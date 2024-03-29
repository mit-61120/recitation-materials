#pragma once

#include "../ast/Visitor.h"
#include "LValueResolver.h"

#include <map>
#include <string>

struct Value {};

struct Integer : public Value {
    int32_t value;
};

struct Record : public Value {
    std::map<std::string, Value*> values;
};

class Interpreter : public ast::RecursiveVisitor {
private:
    Value* result;

    // in your code, define a proper class; it needs a parent pointer and it can change during function calls.
    std::map<std::string, Value*> frame;
    friend class LValueResolver;

    LValueResolver lValueResolver{*this};

public:
    void visit(const ast::Assignment &op) override;

    void visit(const ast::Name &op) override;

    void visit(const ast::FieldDereference &op) override;

    void visit(const ast::Int &op) override;

    void visit(const ast::Record &op) override;
};

