#include "InstCount.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

PreservedAnalyses InstCount::run(Function& F, FunctionAnalysisManager&)
{
  // IVY: This is an answer!!!!!
  //========--------  Answer --------==========
  int count_ins = 0;
  for (BasicBlock& BB : F) {
    for (Instruction& I : BB) {
      count_ins++;
    }
  }
  dbgs() << "Running MyPass on function: " << F.getName() << "Ins count: " << count_ins << "\n";
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
            if (Name == "inst-count") {
              FPM.addPass(InstCount());
              return true;
            }
            return false;
          });
    }
  };
}
