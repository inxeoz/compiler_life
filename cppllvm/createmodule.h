// createmodule.h
#ifndef CREATEMODULE_H
#define CREATEMODULE_H

#include <llvm/IR/Module.h> // Include for llvm::Module
#include <llvm/IR/LLVMContext.h> // Include for llvm::LLVMContext

llvm::Module* createModule(llvm::LLVMContext& context);

#endif // CREATEMODULE_H
