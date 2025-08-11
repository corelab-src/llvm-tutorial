#ifndef LLVM_TUTORIAL_OPTIMIZATION_INSERT_INC_FUNCTION_H
#define LLVM_TUTORIAL_OPTIMIZATION_INSERT_INC_FUNCTION_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

namespace {
struct InsertIncFunction : PassInfoMixin<InsertIncFunction> {
  PreservedAnalyses run(Module& M, ModuleAnalysisManager& MAM);
};
} // namespace

#endif
