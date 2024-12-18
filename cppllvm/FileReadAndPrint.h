#ifndef FILEREADANDPRINT_H
#define FILEREADANDPRINT_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

using namespace llvm;

class FileReadAndPrint {
public:
    FileReadAndPrint(LLVMContext& context, Module* module);
    void declareFunctions();
    void createGlobalConstants();
    void defineMainFunction();

private:
    LLVMContext& context;
    Module* module;
    IRBuilder<> builder;

    void declareFopen();
    void declarePrintf();
    void declareFgetc();
    void createModeConstant();
    void createErrMsgConstant();
    void createFmtCharConstant();
    void createMainFunctionPrototype();
};

#endif
