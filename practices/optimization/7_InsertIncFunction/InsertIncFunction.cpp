#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

#include "InsertIncFunction.h"

PreservedAnalyses InsertIncFunction::run(Module& M, ModuleAnalysisManager& MAM)
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
            if (Name == "insert-inc-fun") {
              MPM.addPass(InsertIncFunction());
              return true;
            }
            return false;
          });
    }
  };
}
