#include "FileReadAndPrint.h"

FileReadAndPrint::FileReadAndPrint(LLVMContext& context, Module* module)
    : context(context), module(module), builder(context) {}

void FileReadAndPrint::declareFunctions() {
    declareFopen();
    declarePrintf();
    declareFgetc();
}

void FileReadAndPrint::declareFopen() {
    FunctionType *FopenType = FunctionType::get(builder.getInt8PtrTy(), {builder.getInt8PtrTy(), builder.getInt8PtrTy()}, false);
    Function::Create(FopenType, Function::ExternalLinkage, "fopen", module);
}

void FileReadAndPrint::declarePrintf() {
    FunctionType *PrintfType = FunctionType::get(builder.getInt32Ty(), {builder.getInt8PtrTy()}, true);
    Function::Create(PrintfType, Function::ExternalLinkage, "printf", module);
}

void FileReadAndPrint::declareFgetc() {
    FunctionType *FgetcType = FunctionType::get(builder.getInt32Ty(), {builder.getInt8PtrTy()}, false);
    Function::Create(FgetcType, Function::ExternalLinkage, "fgetc", module);
}

void FileReadAndPrint::createGlobalConstants() {
    createModeConstant();
    createErrMsgConstant();
    createFmtCharConstant();
}

void FileReadAndPrint::createModeConstant() {
    module->getOrInsertGlobal("mode", ArrayType::get(builder.getInt8Ty(), 2));
    GlobalVariable *Mode = module->getNamedGlobal("mode");
    Mode->setInitializer(ConstantDataArray::getString(context, "r", true));
}

void FileReadAndPrint::createErrMsgConstant() {
    module->getOrInsertGlobal("err_msg", ArrayType::get(builder.getInt8Ty(), 19));
    GlobalVariable *ErrMsg = module->getNamedGlobal("err_msg");
    ErrMsg->setInitializer(ConstantDataArray::getString(context, "File open failed!\n", true));
}

void FileReadAndPrint::createFmtCharConstant() {
    module->getOrInsertGlobal("fmt_char", ArrayType::get(builder.getInt8Ty(), 3));
    GlobalVariable *FmtChar = module->getNamedGlobal("fmt_char");
    FmtChar->setInitializer(ConstantDataArray::getString(context, "%c", true));
}

void FileReadAndPrint::defineMainFunction() {
    createMainFunctionPrototype();
}

void FileReadAndPrint::createMainFunctionPrototype() {
    FunctionType *MainType = FunctionType::get(builder.getInt32Ty(), {builder.getInt32Ty(), builder.getInt8PtrTy()->getPointerTo()}, false);
    Function *MainFunc = Function::Create(MainType, Function::ExternalLinkage, "main", module);
    BasicBlock *Entry = BasicBlock::Create(context, "entry", MainFunc);
    builder.SetInsertPoint(Entry);
}
