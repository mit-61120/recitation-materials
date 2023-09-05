#pragma once

#include <iostream>
#include <cassert>

#include "antlr4-runtime.h"
#include "MITScript.h"
#include "AST.h"

namespace AST {

class Parser {
private:
    MITScript* lexer_p;
    antlr4::CommonTokenStream* tokens_p;
    antlr4::Token* current_token;
    bool errored;

    void ErrorOut(antlr4::Token* token, std::string message);

    bool ended() const;

    void consume(size_t token_type);

    void consume(std::vector<size_t> token_types);

public:
    Parser(antlr4::CommonTokenStream* tokens);

    // PROGRAM : STATEMENT* ;
    std::shared_ptr<Program> ParseProgram();

    bool failed() const;

private:
    // STATEMENT : ( ASSIGNMENT | IFSTATEMENT ) ;
    std::shared_ptr<Stmt> ParseStmt();

    // ASSIGNMENT : LHS ASSIGN_KEY EXPRESSION SCOLON_KEY ;
    std::shared_ptr<Assignment> ParseAssignment();

    // BLOCK : OBRACK_KEY ( STATEMENT )* CBRACK_KEY ;
    std::shared_ptr<Block> ParseBlock();

    // IFSTATEMENT : IF_KEY OPAREN_KEY EXPRESSION CPAREN_KEY BLOCK ;
    std::shared_ptr<If> ParseIf();

    // EXPRESSION : PREDICATE ;
    std::shared_ptr<Expr> ParseExpr();

    // PREDICATE : ARITHMETIC ( (LT_KEY | EQ_KEY) ARITHMETIC )? ;
    std::shared_ptr<Expr> ParsePredicate();

    // ARITHMETIC : PRODUCT ( ( ADD_KEY | SUB_KEY ) PRODUCT )* ;
    std::shared_ptr<Expr> ParseArithmetic();

    // PRODUCT : UNIT ( MUL_KEY UNIT )* ;
    std::shared_ptr<Expr> ParseProduct();

    // UNIT : ( LHS | CONSTANT | OPAREN_KEY PREDICATE CPAREN_KEY ) ;
    std::shared_ptr<Expr> ParseUnit();

    // LHS : NAME ;
    std::shared_ptr<Var> ParseLHS();

    // CONSTANT : ( INT_CONSTANT | BOOL_CONSTANT | NONE_CONSTANT ) ;
    std::shared_ptr<Expr> ParseConstant();

private: // helper functions

    // helper function to trim a string constant
    std::string trim(std::string str) const;

    // checks if the current_token is any constant value
    bool CurrentTokenIsConstant() const;

    // helper function for fetching the current BinOp key
    BinOp::Op GetCurrentBinOp() const;

    // helper function for fetching a MITScript::Name
    std::string GetCurrentName();
};


} // namespace AST
