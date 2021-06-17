#ifndef VISITOR_H
#define VISITOR_H

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>

class ASTNode;
class BinaryOp;
class UnaryOp;
class ConditionalOp;
class FuncCall;
class Identifier;
class Object;
class Enumerator;
class Constant;
class TempVar;

class Declaration;
class IfStmt;
class JumpStmt;
class ReturnStmt;
class LabelStmt;
class EmptyStmt;
class CompoundStmt;
class FuncDecl;
class Parameter;
class Program;

class Visitor {
public:
  virtual ~Visitor() {}
  virtual llvm::Value* VisitASTNode(ASTNode* node) = 0;
  virtual llvm::Value* VisitBinaryOp(BinaryOp* binary) = 0;
  virtual llvm::Value* VisitUnaryOp(UnaryOp* unary) = 0;
  virtual llvm::Value* VisitConditionalOp(ConditionalOp* cond) = 0;
  virtual llvm::Value* VisitFuncCall(FuncCall* funcCall) = 0;
  virtual llvm::Value* VisitEnumerator(Enumerator* enumer) = 0;
  virtual llvm::Value* VisitIdentifier(Identifier* ident) = 0;
  virtual llvm::Value* VisitObject(Object* obj) = 0;
  virtual llvm::Value* VisitConstant(Constant* cons) = 0;
  virtual llvm::Value* VisitTempVar(TempVar* tempVar) = 0;

  virtual llvm::Value* VisitDeclaration(Declaration* decl) = 0;
  virtual llvm::Value* VisitIfStmt(IfStmt* ifStmt) = 0;
  virtual llvm::Value* VisitJumpStmt(JumpStmt* jumpStmt) = 0;
  virtual llvm::Value* VisitReturnStmt(ReturnStmt* returnStmt) = 0;
  virtual llvm::Value* VisitLabelStmt(LabelStmt* labelStmt) = 0;
  virtual llvm::Value* VisitEmptyStmt(EmptyStmt* emptyStmt) = 0;
  virtual llvm::Value* VisitCompoundStmt(CompoundStmt* compStmt) = 0;
  virtual llvm::Value* VisitFuncDecl(FuncDecl* funcDecl) = 0;
  virtual llvm::Value* VisitParameter(Parameter* parameter) = 0;
  virtual void         VisitProgram(Program* program) = 0;
};
#endif 