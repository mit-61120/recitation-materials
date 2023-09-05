#include "compile.h"
#include "instructions.h"

#include <map>

namespace CFG {

void placeBB(InstructionList& instructions, std::map<BasicBlock*, int32_t>& locs, std::map<int32_t, BasicBlock*>& targets, BasicBlock* bb) {
	if (bb == nullptr || locs.find(bb) != locs.end()) {
		return;
	}

	locs[bb] = instructions.size();
	instructions.insert(instructions.end(), bb->instructions.begin(), bb->instructions.end());
	if (bb->falseTarget) {
		instructions.push_back(Instruction(Operation::Not, std::optional<int32_t>()));
		instructions.push_back(Instruction(Operation::If, 0));
		targets[instructions.size() - 1] = bb->falseTarget;
		placeBB(instructions, locs, targets, bb->trueTarget);
		placeBB(instructions, locs, targets, bb->falseTarget);
	} else {
		placeBB(instructions, locs, targets, bb->trueTarget);
	}
}

void fixJumps(InstructionList& instructions, std::map<BasicBlock*,int32_t>& locs, std::map<int32_t, BasicBlock*>& targets) {
	for (int32_t i = 0; i < instructions.size(); ++i) {
		if (targets.find(i) != targets.end()) {
			int32_t target = locs[targets[i]];
			instructions[i] = Instruction(Operation::If, target - i);
		}
	}
}

Function compile(CFG::Builder& builder) {
	Function func;
	func.parameter_count_ = 0;
	func.constants_ = builder.constants;
	func.names_ = builder.names;

	std::map<BasicBlock*, int32_t> locs;
	std::map<int32_t, BasicBlock*> targets;
	placeBB(func.instructions, locs, targets, builder.cfg->entry);
	fixJumps(func.instructions, locs, targets);

	return func;
}

}  // namspace CFG
