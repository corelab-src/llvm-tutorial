#ifndef LLVM_TUTORIAL_OPTIMIZATION_FUNCTION_NAME_PRINTER_H
#define LLVM_TUTORIAL_OPTIMIZATION_FUNCTION_NAME_PRINTER_H

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

namespace {
struct FunctionNamePrinter : PassInfoMixin<FunctionNamePrinter> {
  PreservedAnalyses run(Function& F, FunctionAnalysisManager&);
};
} // namespace

#endif
