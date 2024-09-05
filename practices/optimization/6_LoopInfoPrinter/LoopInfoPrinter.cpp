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

    for (Loop *L : LI) {
	q.push(L);
	dbgs() << "Loop Name: " << L->getName() << "\n";
	dbgs() << "  Depth of Loop: " << L->getLoopDepth() << "\n";
	PHINode *Node = L->getCanonicalInductionVariable();
	if (Node) {
	    dbgs() << "  Induction Variable: \n";
	    Node->dump();
	}

	while(!q.empty()){
	  Loop *LL = q.front();
	  if(LL->isInnermost()){
		dbgs() << "  Max Depth of Loop: " << LL->getLoopDepth() << "\n";
	  } 
	  else{
		for(Loop *subLoop : LL->getSubLoopsVector()){
		  q.push(subLoop);
		}
	  }	
	  q.pop();
	}

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
