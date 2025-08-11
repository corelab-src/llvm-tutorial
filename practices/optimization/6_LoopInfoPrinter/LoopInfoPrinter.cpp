#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

#include "LoopInfoPrinter.h"
#include "llvm/Analysis/LoopInfo.h"

PreservedAnalyses LoopInfoPrinter::run(Function& F, FunctionAnalysisManager& FAM)
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
            if (Name == "loop-info-printer") {
              FPM.addPass(LoopInfoPrinter());
              return true;
            }
            return false;
          });
    }
  };
}
