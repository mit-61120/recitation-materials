#include <iostream>
#include <cassert>

#include "antlr4-runtime.h"
#include "MITScript.h"
#include "AST.h"
#include "Parser.h"
#include "CFGBuilder.h"
#include "compile.h"
#include "prettyprinter.h"

using namespace std;

shared_ptr<Program> ParseProgram(antlr4::CommonTokenStream &tokens) {
  AST::Parser parser(&tokens);
  try {
    shared_ptr<Program> program = parser.ParseProgram();
    bool failed = parser.failed();

    if(failed) {
      throw SystemException("Failed to parse.");
    } else {
      return program;
    }
  } catch (SystemException &se) {
    throw SystemException("Parser returned: " + se.msg_);
  }
}

int main(int argc, const char *argv[])
{
  // We will now have the interpreter take the input
  // program from a file
  if (argc != 2)
  {
    std::cout <<"Usage: mitscript <filename>\n";
    return 1;
  }

  std::ifstream file;
  file.open(argv[1]);

  if (!file.is_open())
  { 
      std::cout <<"Failed to open file: " <<argv[1] <<"\n";
      return 1;
  }

  // Create lexer
  antlr4::ANTLRInputStream input(file);
  MITScript lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);

  // Load all tokens within the file to a buffer
  tokens.fill();

  shared_ptr<Program> program = nullptr;

  try {
    program = ParseProgram(tokens);


  } catch (SystemException &se) {
    cerr << se.msg_ << endl;
    return 1;
  }


  if (program == nullptr) {
    // Print error messages if you'd like
    cerr << "ParseProgram returned nullptr" << endl;
    return 1;
  }

	CFG::Builder builder;
	program->accept(&builder);
	std::cout << *builder.cfg << std::endl;

  Function compiled = CFG::compile(builder);
	PrettyPrinter().print(compiled, std::cout);
	std::cout << std::endl;

  return 0;
}
