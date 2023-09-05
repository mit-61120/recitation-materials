#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "CFG.h"
#include "Visitor.h"
#include "instructions.h"
#include "types.h"

namespace CFG {

struct Builder final : public Visitor {
  // Stmts
  virtual void visit(const Block *op) override;
  virtual void visit(const If *op) override;
  virtual void visit(const Assignment *op) override;

  // Exprs
  virtual void visit(const Int *op) override;
  virtual void visit(const Bool *op) override;
  virtual void visit(const Var *op) override;
  virtual void visit(const BinOp *op) override;

  // return values
  ControlFlowGraph *cfg = nullptr;
  InstructionList instructions;

  std::vector<Constant *> constants;
  std::vector<std::string> names;

 private:
  std::map<std::string, int32_t> nameMap;
  std::map<int32_t, int32_t> intMap;

  int32_t falseIndex = -1;
  int32_t trueIndex = -1;

  int32_t allocateName(const std::string &name) {
    auto iter = nameMap.find(name);
    if (iter == nameMap.end()) {
      int32_t index = names.size();
      nameMap[name] = index;
      names.push_back(name);
      return index;
    } else {
      return iter->second;
    }
  }

  int32_t allocateIntConstant(int32_t value) {
    auto iter = intMap.find(value);
    if (iter == intMap.end()) {
      int32_t index = constants.size();
      intMap[value] = index;
      constants.push_back(new Integer(value));
      return index;
    } else {
      return iter->second;
    }
  }

  int32_t allocateBoolConstant(bool value) {
    if (value) {
      if (trueIndex == -1) {
        int32_t index = constants.size();
        trueIndex = index;
        constants.push_back(new Boolean(value));
        return index;
      } else {
        return trueIndex;
      }
    } else {
      if (falseIndex == -1) {
        int32_t index = constants.size();
        falseIndex = index;
        constants.push_back(new Boolean(value));
        return index;
      } else {
        return falseIndex;
      }
    }
  }
};

}  // namespace CFG
