#include "PrintEven.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

PreservedAnalyses PrintEven::run(Module& M, ModuleAnalysisManager& MAM)
{
  // IVY: This is an answer!!!!!
  //========--------  Answer --------==========
  Function* F = M.getFunction("printInt");
  if (F == nullptr) {
    errs() << "Function 'printInt' not found in the module.\n";
    return PreservedAnalyses::all();
  }

  LLVMContext& Context = M.getContext();
  BasicBlock* Entry = &(F->getEntryBlock());

  Instruction* SplitInst;
  for (Instruction& I : *Entry) {
    if (CallInst* CI = dyn_cast<CallInst>(&I)) {
      if (CI->getCalledFunction()->getName() == "printf") {
        SplitInst = &I;
        break;
      }
    }
  }

  if (!SplitInst) {
    errs() << "No call instruction found in the entry block.\n";
    return PreservedAnalyses::all();
  }

  BasicBlock* Split = Entry->splitBasicBlock(SplitInst, "split");
  Split->getTerminator()->eraseFromParent();

  BasicBlock* ReturnBlock = BasicBlock::Create(Context, "return", F);
  IRBuilder<> RetBuilder(ReturnBlock);
  RetBuilder.CreateRetVoid();

  IRBuilder<> SplitBuilder(Split);
  SplitBuilder.CreateBr(ReturnBlock);

  IRBuilder<> EntryBuilder(Entry);
  Entry->getTerminator()->eraseFromParent();
  Value* Zero = ConstantInt::get(Type::getInt32Ty(Context), 0);
  Value* Two = ConstantInt::get(Type::getInt32Ty(Context), 2);
  Value* Remainder = EntryBuilder.CreateSRem(F->arg_begin(), Two, "remainder");
  Value* IsEven = EntryBuilder.CreateICmpEQ(Remainder, Zero, "is_even");
  BranchInst* Branch = EntryBuilder.CreateCondBr(IsEven, Split, ReturnBlock);

  //========--------  Answer --------==========

  return PreservedAnalyses::none();
}

extern "C" ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo()
{
  return {
    LLVM_PLUGIN_API_VERSION, "Hello_Pass", LLVM_VERSION_STRING,
    [](PassBuilder& PB) {
      PB.registerPipelineParsingCallback(
          [](StringRef Name, ModulePassManager& MPM,
              ArrayRef<PassBuilder::PipelineElement>) {
            if (Name == "print-even") {
              MPM.addPass(PrintEven());
              return true;
            }
            return false;
          });
    }
  };
}
