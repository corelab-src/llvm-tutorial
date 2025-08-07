#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

// IVY: Remove this too
#include "LoopInfoPrinter.h"
#include "llvm/Analysis/LoopInfo.h"

PreservedAnalyses LoopInfoPrinter::run(Function& F, FunctionAnalysisManager& FAM)
{
  // IVY: This is an answer!!!!!
  //========--------  Answer --------==========
  LoopInfo& LI = FAM.getResult<LoopAnalysis>(F);
  for (Loop* L : LI.getLoopsInPreorder()) {
    dbgs() << "Loop Name: " << L->getName() << "\n";
    dbgs() << "Loop ID: " << L->getLoopID() << "\n";
    dbgs() << "Loop Depth: " << L->getLoopDepth() << "\n";
    PHINode* Node = L->getCanonicalInductionVariable();
    if (Node) {
      dbgs() << "Canonical Induction Variable: " << *Node << "\n";
      Node->dump();
    }
    dbgs() << "\n";
  }
  dbgs() << "Function: " << F.getName() << " includes " << LI.getLoopsInPreorder().size() << " Loops in total\n";
  dbgs() << LI.getTopLevelLoops().size() << " are top-level loops\n";
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
