#include "CFG.h"

#include "prettyprinter.h"

namespace CFG {
std::ostream& operator<<(std::ostream& os, const BasicBlock& bb) {
  os << &bb << std::endl;
  os << "======================" << std::endl;
  PrettyPrinter().print(bb.instructions, os);
  os << "----------------------" << std::endl;
  os << "true: " << bb.trueTarget << std::endl;
  os << "false: " << bb.falseTarget << std::endl;
  os << "======================" << std::endl;
  return os;
}

void printBB(std::ostream& os, BasicBlock* bb, std::set<BasicBlock*>& printed) {
  if (bb == nullptr || printed.find(bb) != printed.end()) {
    return;
  }
  printed.insert(bb);
  std::cout << *bb << std::endl;
  printBB(os, bb->trueTarget, printed);
  printBB(os, bb->falseTarget, printed);
}

// DFS on CFG
void gather(BasicBlock* bptr, std::set<BasicBlock*>& bset) {
  if (bptr && bset.find(bptr) != bset.end()) {
    return;
  } else {
    bset.insert(bptr);
    if (bptr->trueTarget) {
      gather(bptr->trueTarget, bset);
    }
    if (bptr->falseTarget) {
      gather(bptr->falseTarget, bset);
    }
  }
}

// custom destructor only called on compiled CFGs
void ControlFlowGraph::destruct() {
  if (entry) {
    std::set<BasicBlock*> visited;
    gather(entry, visited);
    for (auto* elem : visited) {
      delete elem;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const ControlFlowGraph& cfg) {
  std::set<BasicBlock*> printed;
  printBB(os, cfg.entry, printed);
  return os;
}

}  // namespace CFG
