#pragma once

#include <memory>
#include <expected>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include "AST.hpp"
#include "Diagnostic.hpp"

class CodeGenerator {
public:
  CodeGenerator()
      : builder_(context_),
        module_(std::make_unique<llvm::Module>("chagylgan", context_)) {}

  void generate(const Statement &statement) {
    create_main();
    generate_statement(statement);
  }

private:
  llvm::LLVMContext context_;
  llvm::IRBuilder<> builder_;
  std::unique_ptr<llvm::Module> module_;

  void create_main() {
    llvm::FunctionType *type =
        llvm::FunctionType::get(builder_.getInt32Ty(), false);

    llvm::Function *main_function = llvm::Function::Create(
        type, llvm::Function::ExternalLinkage, "main", *module_);

    llvm::BasicBlock *entry =
        llvm::BasicBlock::Create(context_, "entry", main_function);

    builder_.SetInsertPoint(entry);
  }

  std::expected<void, Diagnostic>
  generate_statement(const Statement &statement);
};
