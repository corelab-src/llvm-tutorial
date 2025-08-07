#include "CallCount.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

PreservedAnalyses CallCount::run(Function& F, FunctionAnalysisManager&)
{
  // IVY: This is an answer!!!!!
  //========--------  Answer --------==========
  int call_count = 0;
  for (BasicBlock& BB : F) {
    for (Instruction& I : BB) {
      if (isa<CallInst>(&I)) {
        call_count++;
      }
    }
  }
  dbgs() << "Function " << F.getName() << " has " << call_count << " of CallInst.\n";

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
