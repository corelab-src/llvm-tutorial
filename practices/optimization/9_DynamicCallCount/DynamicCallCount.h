#ifndef LLVM_TUTORIAL_OPTIMIZATION_DYNAMIC_CALL_COUNT_H
#define LLVM_TUTORIAL_OPTIMIZATION_DYNAMIC_CALL_COUNT_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

namespace {
struct DynamicCallCount : PassInfoMixin<DynamicCallCount> {
  PreservedAnalyses run(Module& M, ModuleAnalysisManager& MAM);
};
} // namespace

#endif
