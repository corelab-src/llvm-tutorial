#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

#include "InsertIncFunction.h"

PreservedAnalyses InsertIncFunction::run(Module& M, ModuleAnalysisManager& MAM)
{
  // IVY: This is an answer!!!!!
  //========--------  Answer --------==========
  LLVMContext& Context = M.getContext();
  FunctionType* IncFuncType = FunctionType::get(
      Type::getInt32Ty(Context), { Type::getInt32Ty(Context) }, false);
  Function* IncFunc = Function::Create(IncFuncType, GlobalValue::ExternalLinkage, "inc", &M);
  BasicBlock* EntryBB = BasicBlock::Create(Context, "entry", IncFunc);
  IRBuilder<> Builder(EntryBB);
  Value* input_arg = IncFunc->arg_begin();
  AllocaInst* Arg = Builder.CreateAlloca(Type::getInt32Ty(Context), nullptr, "arg");
  Builder.CreateStore(input_arg, Arg);
  Value* Arg_Load = Builder.CreateLoad(Type::getInt32Ty(Context), Arg, "arg_load");
  ConstantInt* One = ConstantInt::get(Type::getInt32Ty(Context), 1);
  Value* Result = Builder.CreateAdd(Arg_Load, One, "result");
  Builder.CreateRet(Result);
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
            if (Name == "insert-inc-fun") {
              MPM.addPass(InsertIncFunction());
              return true;
            }
            return false;
          });
    }
  };
}
