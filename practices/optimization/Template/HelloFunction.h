#ifndef LLVM_TUTORIAL_OPTIMIZATION_TEMPLATE_HELLO_FUNCTION_H
#define LLVM_TUTORIAL_OPTIMIZATION_TEMPLATE_HELLO_FUNCTION_H

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

namespace {
struct HelloFunction : PassInfoMixin<HelloFunction> {
  PreservedAnalyses run(Function& F, FunctionAnalysisManager& FAM);
};
} // namespace

#endif
