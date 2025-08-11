#include "llvm/Support/raw_ostream.h"

#include "HelloFunction.h"

#define DEBUG_TYPE "hello"

PreservedAnalyses HelloFunction::run(Function& F, FunctionAnalysisManager& FAM)
{
  errs() << "HelloFunction Pass Called!" << "\n";
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
            if (Name == "hello-function") {
              FPM.addPass(HelloFunction());
              return true;
            }
            return false;
          });
    }
  };
}
