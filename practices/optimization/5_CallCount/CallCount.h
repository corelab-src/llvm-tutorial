#ifndef LLVM_TUTORIAL_OPTIMIZATION_CALL_COUNT_H
#define LLVM_TUTORIAL_OPTIMIZATION_CALL_COUNT_H

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

namespace {
struct CallCount : PassInfoMixin<CallCount> {
  PreservedAnalyses run(Function& F, FunctionAnalysisManager&);
};
} // namespace

#endif
