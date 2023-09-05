#include "CFGBuilder.h"
#include <cassert>

namespace CFG {

void Builder::visit(const Block *op) {
    ControlFlowGraph *block = nullptr;
    for (const auto & s : op->_stmts) {
        s->accept(this);
        if (block == nullptr) {
            // first case
            block = cfg;
        } else {
            block->exit->trueTarget = cfg->entry;
            block->exit = cfg->exit;
        }
    }
    cfg = block;
}

void Builder::visit(const If *op) {
    op->_cond->accept(this);
    BasicBlock *condBB = new BasicBlock(instructions);
    op->_then->accept(this);
    ControlFlowGraph *ifBody = cfg;
    condBB->trueTarget = ifBody->entry;
    // Dummy ender
    BasicBlock *endBB = new BasicBlock({});
    condBB->falseTarget = endBB;
    ifBody->exit->trueTarget = endBB;
    cfg = new ControlFlowGraph(condBB, endBB);
}

void Builder::visit(const Assignment *op) {
    op->_value->accept(this);
    InstructionList insts = instructions;
		std::string var = op->_lhs->_name;
		int32_t index = allocateName(var);
		insts.push_back(Instruction(Operation::StoreGlobal, index));
		BasicBlock *bb = new BasicBlock(insts);
		cfg = new ControlFlowGraph(bb, bb);
}

void Builder::visit(const Int *op) {
    int32_t index = allocateIntConstant(op->_value);
    instructions = {Instruction(Operation::LoadConst, index)};
}

void Builder::visit(const Bool *op) {
    int32_t index = allocateBoolConstant(op->_value);
    instructions = {Instruction(Operation::LoadConst, index)};
}

void Builder::visit(const Var *op) {
    int32_t index = allocateName(op->_name);
    instructions = {Instruction(Operation::LoadGlobal, index)};
}

void Builder::visit(const BinOp *op) {
    op->_a->accept(this);
    InstructionList instrs = instructions;
    op->_b->accept(this);
    instrs.insert(instrs.end(), instructions.begin(), instructions.end());
    // Now we have a and b computed
    switch(op->_op) {
        case BinOp::Eq: {
            instrs.push_back(Instruction(Operation::Eq, std::optional<int32_t>()));
            break;
        }
        case BinOp::Mul: {
            instrs.push_back(Instruction(Operation::Mul, std::optional<int32_t>()));
            break;
        }
        default: {
            std::cerr << "didn't implement enough instructions yet\n";
            assert(false);
        }
    }
    instructions = std::move(instrs);
}

}  // namespace CFG