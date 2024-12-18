#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include "createmodule.h"

llvm::Module* createModule(llvm::LLVMContext &context) {
    auto *module = new llvm::Module("my_module", context);
    return module;
}
