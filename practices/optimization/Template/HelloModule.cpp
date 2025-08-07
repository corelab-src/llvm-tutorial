#include "HelloModule.h"
#include "llvm/Support/raw_ostream.h"

PreservedAnalyses HelloModule::run(Module& M, ModuleAnalysisManager& MAM)
{
  errs() << "HelloModule Pass called!" << "\n";
  return PreservedAnalyses::all();
}

extern "C" ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo()
{
  return {
    LLVM_PLUGIN_API_VERSION, "Hello_Pass", LLVM_VERSION_STRING,
    [](PassBuilder& PB) {
      PB.registerPipelineParsingCallback(
          [](StringRef Name, ModulePassManager& MPM,
              ArrayRef<PassBuilder::PipelineElement>) {
            if (Name == "hello-module") {
              MPM.addPass(HelloModule());
              return true;
            }
            return false;
          });
    }
  };
}
