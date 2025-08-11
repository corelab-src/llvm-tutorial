#include "CallCount.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

PreservedAnalyses CallCount::run(Function& F, FunctionAnalysisManager&)
{
  //========--------  Answer --------==========

  //========--------  Answer --------==========

  return PreservedAnalyses::all();
}

extern "C" ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo()
{
  return {
    LLVM_PLUGIN_API_VERSION, "Hello_Pass", LLVM_VERSION_STRING,
    [](PassBuilder& PB) {
      PB.registerPipelineParsingCallback(
          [](StringRef Name, FunctionPassManager& FPM,
              ArrayRef<PassBuilder::PipelineElement>) {
            if (Name == "callcount") {
              FPM.addPass(CallCount());
              return true;
            }
            return false;
          });
    }
  };
}
