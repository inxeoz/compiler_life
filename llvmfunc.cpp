#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Verifier.h>

using namespace llvm;

void createLLVMModule(std::unique_ptr<Module>& module, LLVMContext& context) {
    // Declare the printf function (external)
    FunctionType *printfType = FunctionType::get(IntegerType::getInt32Ty(context), {PointerType::get(IntegerType::getInt8Ty(context), 0)}, true);
    Function *printfFunc = Function::Create(printfType, Function::ExternalLinkage, "printf", *module);

    // Create the string constant for printf
    Constant *str = ConstantDataArray::getString(context, "hello");
    GlobalVariable *strGlobal = new GlobalVariable(*module, str->getType(), true, GlobalValue::PrivateLinkage, str, ".str");

    // Create the main function
    FunctionType *mainType = FunctionType::get(IntegerType::getInt32Ty(context), false);
    Function *mainFunc = Function::Create(mainType, Function::ExternalLinkage, "main", *module);

    // Create an entry block for the main function
    BasicBlock *entryBlock = BasicBlock::Create(context, "entry", mainFunc);
    IRBuilder<> builder(entryBlock);

    // Allocate an integer variable %i and set it to 0
    AllocaInst *i = builder.CreateAlloca(IntegerType::getInt32Ty(context), nullptr, "i");
    builder.CreateStore(ConstantInt::get(IntegerType::getInt32Ty(context), 0), i);

    // Create a loop: we will jump to the 'loop' block
    BasicBlock *loopBlock = BasicBlock::Create(context, "loop", mainFunc);
    builder.CreateBr(loopBlock);

    // Add the loop body and end blocks
    BasicBlock *bodyBlock = BasicBlock::Create(context, "body", mainFunc);
    BasicBlock *endBlock = BasicBlock::Create(context, "end", mainFunc);

    builder.SetInsertPoint(loopBlock);

    // Load the value of %i
    LoadInst *count = builder.CreateLoad(i, "count");
    Value *cmp = builder.CreateICmpSLT(count, ConstantInt::get(IntegerType::getInt32Ty(context), 5), "cmp");

    // Branch based on the comparison
    builder.CreateCondBr(cmp, bodyBlock, endBlock);

    builder.SetInsertPoint(bodyBlock);

    // Call printf to print the string
    Value *strPtr = builder.CreateGEP(strGlobal, {ConstantInt::get(Type::getInt32Ty(context), 0), ConstantInt::get(Type::getInt32Ty(context), 0)});
    builder.CreateCall(printfFunc, {strPtr});

    // Increment %i by 1
    Value *next = builder.CreateAdd(count, ConstantInt::get(IntegerType::getInt32Ty(context), 1), "next");
    builder.CreateStore(next, i);

    // Go back to the loop
    builder.CreateBr(loopBlock);

    builder.SetInsertPoint(endBlock);

    // Return 0 from the main function
    builder.CreateRet(ConstantInt::get(IntegerType::getInt32Ty(context), 0));

    // Verify the module for correctness
    if (verifyModule(*module, &errs())) {
        errs() << "Module verification failed!\n";
    }
}
