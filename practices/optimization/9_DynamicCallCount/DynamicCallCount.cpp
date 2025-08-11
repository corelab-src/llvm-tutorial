#include "DynamicCallCount.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

PreservedAnalyses DynamicCallCount::run(Module& M, ModuleAnalysisManager& MAM)
{
  //========--------  Answer --------==========

  //========--------  Answer --------==========

  return PreservedAnalyses::none();
}

extern "C" ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo()
{
  return {
    LLVM_PLUGIN_API_VERSION, "Hello_Pass", LLVM_VERSION_STRING,
    [](PassBuilder& PB) {
      PB.registerPipelineParsingCallback(
          [](StringRef Name, ModulePassManager& MPM,
              ArrayRef<PassBuilder::PipelineElement>) {
            if (Name == "dyn-call-count") {
              MPM.addPass(DynamicCallCount());
              return true;
            }
            return false;
          });
    }
  };
}
