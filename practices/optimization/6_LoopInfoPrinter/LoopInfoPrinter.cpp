#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h" 
#include "llvm/IR/Instructions.h"
//========--------  Answer --------==========
#include "llvm/Analysis/LoopInfo.h"
#include <queue>
//========--------  Answer --------==========

#include "LoopInfoPrinter.h"

bool LoopInfoPrinter::runOnFunction(Function &F) {

    //========--------  Answer --------==========
    LoopInfo &LI = getAnalysis< LoopInfoWrapperPass >().getLoopInfo();
    std::queue<Loop *> q;

    for (Loop *L : LI.getLoopsInPreorder()) {
	q.push(L);
	dbgs() << "Loop Name: " << L->getName() << "\n";
	dbgs() << "Loop ID: " << L->getLoopID() << "\n";
	dbgs() << "Depth of Loop: " << L->getLoopDepth() << "\n";
	if(L->isInnermost()){
		dbgs() << "Innermost Depth of Loop: " << L->getLoopDepth() << "\n";
	} 
	PHINode *Node = L->getCanonicalInductionVariable();
	if (Node) {
	    dbgs() << "  Induction Variable: \n";
	    Node->dump();
	}
	dbgs() << "\n";
  }
    //========--------  Answer --------==========

    return false;
}

void LoopInfoPrinter::getAnalysisUsage(AnalysisUsage &AU) const {

    //========--------  Answer --------==========
    AU.addRequired< LoopInfoWrapperPass >();
    //========--------  Answer --------==========
    AU.setPreservesAll();
}

char LoopInfoPrinter::ID = 0;
static RegisterPass<LoopInfoPrinter> Y("loop-info-printer", "LoopInfoPrinter Pass ");
