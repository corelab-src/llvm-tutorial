#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

#include "InsertIncFunction.h"

bool InsertIncFunction::runOnModule(Module& M)
{
  //========--------  Answer --------==========
  LLVMContext& Context = M.getContext();

  FunctionType* IncFuncType = FunctionType::get(Type::getInt32Ty(Context), Type::getInt32Ty(Context), false);
  Function* incFunc = Function::Create(IncFuncType, GlobalValue::ExternalLinkage, "inc", &M);

  Argument* arg = incFunc->arg_begin();
  BasicBlock* entry = BasicBlock::Create(Context, "entry", incFunc);
  IRBuilder<> Builder(entry);
  AllocaInst* alloc = Builder.CreateAlloca(Type::getInt32Ty(Context), nullptr);
  StoreInst* str = Builder.CreateStore(arg, alloc);
  LoadInst* ld = Builder.CreateLoad(Type::getInt32Ty(Context), alloc);
  Constant* one = ConstantInt::get(Type::getInt32Ty(Context), 1);
  Value* result = Builder.CreateAdd(ld, one);
  Builder.CreateRet(result);
  //========--------  Answer --------==========

  return false;
}

void InsertIncFunction::getAnalysisUsage(AnalysisUsage& AU) const
{
  AU.setPreservesAll();
}

char InsertIncFunction::ID = 0;
static RegisterPass<InsertIncFunction> X("insert-inc-fun", "Hello World Pass ");
