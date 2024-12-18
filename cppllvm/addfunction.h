// addfunction.h
#ifndef ADDFUNCTION_H
#define ADDFUNCTION_H

#include <llvm/IR/Module.h>   // Include for llvm::Module
#include <llvm/IR/LLVMContext.h> // Include for llvm::LLVMContext

void addFunction(llvm::Module *module);

#endif // ADDFUNCTION_H