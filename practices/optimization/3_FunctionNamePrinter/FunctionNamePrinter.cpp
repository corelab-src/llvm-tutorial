#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

#include "FunctionNamePrinter.h"

PreservedAnalyses FunctionNamePrinter::run(Function& F, FunctionAnalysisManager&)
{
  // IVY: This is an answer!!!!!
  //========--------  Answer --------==========
  dbgs() << "Function Name: " << F.getName() << "\n";
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
            if (Name == "fun-name-printer") {
              FPM.addPass(FunctionNamePrinter());
              return true;
            }
            return false;
          });
    }
  };
}
