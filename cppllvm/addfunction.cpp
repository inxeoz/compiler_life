#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Module.h>
#include "addfunction.h"

void addFunction(llvm::Module *module) {
    llvm::LLVMContext &context = module->getContext();
    llvm::FunctionType *funcType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context), false);

    llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, "my_function", module);
}
//
// Created by inxeoz on 12/19/24.
//
