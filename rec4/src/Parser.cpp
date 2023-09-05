#include "Parser.h"

using namespace std;

namespace AST {

bool contains(vector<size_t> types, size_t t) {
  return count(types.begin(), types.end(), t) > 0;
}

void Parser::ErrorOut(antlr4::Token* token, string message) {
    cout << "Unexpected Symbol (" 
        << token->getLine() <<"," 
        << token->getCharPositionInLine() <<"): "
        << token->getText() << endl
        << token->getType() << endl;

    cout << message << endl;
    // make sure error is recorded for parsing
    errored = true;
    throw SystemException("Failed to parse.");
}

bool Parser::ended() const {
    return current_token->getType() == MITScript::EOF;
}

void Parser::consume(size_t token_type) {
    if (current_token->getType() == token_type) {
        // if types match then consume this token
        tokens_p->consume();
        current_token = tokens_p->get(tokens_p->index());
    } else {
        // not what was expected
        ErrorOut(current_token, "expected wrong type(" + to_string(token_type) + ") for consume");
    }
}

void Parser::consume(vector<size_t> token_types) {
    if (contains(token_types, current_token->getType())) {
        // list contains type of current token
        tokens_p->consume();
        current_token = tokens_p->get(tokens_p->index());
    } else {
        // not what was expected
        string types = "";
        for (auto t : token_types) { types += (to_string(t) + ","); }
        ErrorOut(current_token, "expected wrong type(" + types + ") for consume");
    }
}

Parser::Parser(antlr4::CommonTokenStream* tokens) {
    tokens_p = tokens;
    current_token = tokens_p->get(tokens_p->index());
    errored = false;
}

// PROGRAM : STATEMENT* ;
shared_ptr<Program> Parser::ParseProgram() {
    shared_ptr<Program> program = Program::make();

    while(!ended() && !errored) {
        shared_ptr<Stmt> stmt = ParseStmt();
        program->AddStmt(move(stmt));
    }
    return program;
}

bool Parser::failed() const {
    return errored;
}

// STATEMENT : ( ASSIGNMENT | IFSTATEMENT ) ;
shared_ptr<Stmt> Parser::ParseStmt() {
    auto token = current_token;

    switch(token->getType()) {
        case MITScript::EOF:
        {
            return nullptr;
        }
        case MITScript::IF_KEY:
        {
            return ParseIf();
        }
        default: {
            return ParseAssignment();
        }
    }
}


// ASSIGNMENT : LHS ASSIGN_KEY EXPRESSION SCOLON_KEY ;
shared_ptr<Assignment> Parser::ParseAssignment() {
    auto lhs = ParseLHS();
    consume(MITScript::ASSIGN_KEY);
    shared_ptr<Expr> expr = ParseExpr();
    consume(MITScript::SCOLON_KEY);
    return Assignment::make(std::move(lhs), move(expr));
}

// BLOCK : OBRACK_KEY ( STATEMENT )* CBRACK_KEY ;
shared_ptr<Block> Parser::ParseBlock() {
    shared_ptr<Block> block = Block::make();

    consume(MITScript::OBRACK_KEY);
    while(!ended() && !failed() && current_token->getType() != MITScript::CBRACK_KEY) {
        auto stmt = ParseStmt();
        block->AddStmt(move(stmt));
    }
    consume(MITScript::CBRACK_KEY);

    return block;
}

// IFSTATEMENT : IF_KEY OPAREN_KEY EXPRESSION CPAREN_KEY BLOCK ;
shared_ptr<If> Parser::ParseIf() {
    consume(MITScript::IF_KEY);
    consume(MITScript::OPAREN_KEY);
    shared_ptr<Expr> cond = ParseExpr();
    consume(MITScript::CPAREN_KEY);
    shared_ptr<Block> then = ParseBlock();
    return If::make(cond, then);
}


// EXPRESSION : Predicate ;
shared_ptr<Expr> Parser::ParseExpr() {
    return ParsePredicate();
}

// PREDICATE : ARITHMETIC ( (LT_KEY | EQ_KEY) ARITHMETIC )? ;
shared_ptr<Expr> Parser::ParsePredicate() {
    shared_ptr<Expr> boolUnit = ParseArithmetic();

    static vector<size_t> accepted = {MITScript::LT_KEY, MITScript::EQ_KEY};

    while (!ended() && !failed()) {
        if (!contains(accepted, current_token->getType())) {
            break;
        }
        BinOp::Op op = GetCurrentBinOp();
        if (op == BinOp::Error) {
            break; // was not a binary op
        }
        // consume an accepted binary op value
        consume(accepted);
        shared_ptr<Expr> rhs = ParseArithmetic();
        boolUnit = BinOp::make(op, move(boolUnit), move(rhs));
    }
    return boolUnit;
}

// ARITHMETIC : PRODUCT ( ( ADD_KEY | SUB_KEY ) PRODUCT )* ;
shared_ptr<Expr> Parser::ParseArithmetic() {
    shared_ptr<Expr> product = ParseProduct();

    static vector<size_t> accepted = {MITScript::SUB_KEY, MITScript::ADD_KEY};

    while (!ended() && !failed()) {
        // cout << "\tround of arith\n";
        if (!contains(accepted, current_token->getType())) {
            break;
        }
        BinOp::Op op = GetCurrentBinOp();
        if (op == BinOp::Error) {
            break; // was not a binary op
        }
        // consume an accepted binary op value
        consume(accepted);
        shared_ptr<Expr> rhs = ParseProduct();
        product = BinOp::make(op, move(product), move(rhs));
    }
    return product;
}

// PRODUCT : UNIT ( ( MUL_KEY ) UNIT )* ;
shared_ptr<Expr> Parser::ParseProduct() {
    shared_ptr<Expr> unit = ParseUnit();

    static vector<size_t> accepted = {MITScript::MUL_KEY};

    while (!ended() && !failed()) {
        if (!contains(accepted, current_token->getType())) {
            break;
        }
        BinOp::Op op = GetCurrentBinOp();
        if (op == BinOp::Error) {
            break; // was not a binary op
        }
        // consume an accepted binary op value
        consume(accepted);
        shared_ptr<Expr> rhs = ParseUnit();
        unit = BinOp::make(op, move(unit), move(rhs));
    }
    return unit;
}


// UNIT : ( LHS | CONSTANT | OPAREN_KEY PREDICATE CPAREN_KEY ) ;
shared_ptr<Expr> Parser::ParseUnit() {
    if (current_token->getType() == MITScript::OPAREN_KEY) {
        consume(MITScript::OPAREN_KEY);
        auto value = ParsePredicate();
        consume(MITScript::CPAREN_KEY);
        return value;
    } else if (CurrentTokenIsConstant()) {
        return ParseConstant();
    } else {
        return ParseLHS();
    }
}

// LHS : NAME ( ( PERIOD_KEY NAME ) | ( OINDEX_KEY EXPRESSION CINDEX_KEY ) )* ;
shared_ptr<Var> Parser::ParseLHS() {
    string name = GetCurrentName();
    return Var::make(name);
}

// CONSTANT : ( INT_CONSTANT | BOOL_CONSTANT ) ;
shared_ptr<Expr> Parser::ParseConstant() {
    if (!CurrentTokenIsConstant()) {
        ErrorOut(current_token, "Error in parsing constant");
        return nullptr;
    }

    switch(current_token->getType()) {
        case MITScript::INT_CONSTANT: {
            int value = stoi(current_token->getText());
            consume(MITScript::INT_CONSTANT);
            return Int::make(value);
        }
        case MITScript::TRUE_KEY:
        {
            consume(MITScript::TRUE_KEY);
            return Bool::make(true);
        }
        case MITScript::FALSE_KEY:
        {
            consume(MITScript::FALSE_KEY);
            return Bool::make(false);
        }
        default:
        {
            ErrorOut(current_token, "Error in switch parsing constant");
            return nullptr;
        }
    }
}

// helper function for fetching a MITScript::Name
string Parser::GetCurrentName() {
    string name = current_token->getText();
    consume(MITScript::NAME);
    return name;
}


// helper function for fetching the current BinOp key
BinOp::Op Parser::GetCurrentBinOp() const {
    switch(current_token->getType()) {
        case MITScript::LT_KEY:
        {
            return BinOp::Lt;
        }
        case MITScript::EQ_KEY:
        {
            return BinOp::Eq;
        }
        case MITScript::ADD_KEY:
        {
            return BinOp::Add;
        }
        case MITScript::SUB_KEY:
        {
            return BinOp::Sub;
        }
        case MITScript::MUL_KEY:
        {
            return BinOp::Mul;
        }
        default:
        {
            return BinOp::Error;
        }
    }
}

bool Parser::CurrentTokenIsConstant() const {
    return ((current_token->getType() == MITScript::INT_CONSTANT) ||
            (current_token->getType() == MITScript::TRUE_KEY) ||
            (current_token->getType() == MITScript::FALSE_KEY));
}

// helper function to trim a string constant
string Parser::trim(string str) const {
    if (str.length() < 2) {
        return "";
    }
    return str.substr(1, str.size() - 2);
}

} // namespace AST