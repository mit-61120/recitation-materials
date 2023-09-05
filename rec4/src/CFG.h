#pragma once

#include <iostream>
#include <memory>
#include <set>
#include "instructions.h"

namespace CFG {

class BasicBlock {
public:
	BasicBlock(InstructionList instructions) : instructions(instructions), trueTarget(nullptr), falseTarget(nullptr) {}

	InstructionList instructions;
	BasicBlock *trueTarget;
	BasicBlock *falseTarget;

	friend std::ostream& operator<<(std::ostream& os, const BasicBlock& bb);
};

void printBB(std::ostream& os, BasicBlock *bb, std::set<BasicBlock*>& printed);

class ControlFlowGraph {
public:
	ControlFlowGraph(BasicBlock *entry, BasicBlock *exit) : entry(entry), exit(exit) {}
	void destruct(); // custom destructor called on compiled CFGs only
	
	BasicBlock *entry;
	BasicBlock *exit;
	
	friend std::ostream& operator<<(std::ostream& os, const ControlFlowGraph& cfg);
};

} // namespace CFG