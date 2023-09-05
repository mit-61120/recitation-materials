#pragma once

#include "types.h"
#include "CFG.h"
#include "CFGBuilder.h"

namespace CFG {

Function compile(CFG::Builder &builder);

}  // namespace CFG