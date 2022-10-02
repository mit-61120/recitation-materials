#pragma once

#include "../ast/Visitor.h"

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
    bool write;
    std::map<std::string, Value*>::iterator writeTo;

    // in your code, define a proper class; it needs a parent pointer and it can change during function calls.
    std::map<std::string, Value*> frame;

public:
    void visit(const ast::Assignment &op) override;

    void visit(const ast::Name &op) override;

    void visit(const ast::FieldDereference &op) override;

    void visit(const ast::Int &op) override;
};

