#include "PrintEven.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

PreservedAnalyses PrintEven::run(Module& M, ModuleAnalysisManager& MAM)
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
            if (Name == "print-even") {
              MPM.addPass(PrintEven());
              return true;
            }
            return false;
          });
    }
  };
}
