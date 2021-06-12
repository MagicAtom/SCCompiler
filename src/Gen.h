#ifndef SCC_GEN_H
#define SCC_GEN_H

#include "Ast.h"
#include "Visitor.h"
#include <iostream>
#include <memory>
#include <map>
#include <utility>

class Parser;

class Generator:public Visitor{
public:
    inline Generator(){
        context_ = std::make_unique<llvm::LLVMContext>();
        module_ = std::make_unique<llvm::Module>("SCComplier",*context_);
        builder_ = std::make_unique<llvm::IRBuilder<>>(*context_);
    }
    inline Generator(const std::vector<ASTNode*> & roots):roots_(roots){
        context_ = std::make_unique<llvm::LLVMContext>();
        module_ = std::make_unique<llvm::Module>("SCComplier",*context_);
        builder_ = std::make_unique<llvm::IRBuilder<>>(*context_);
    }
    void Gen();
public: // visitor
    virtual void VisitBinaryOp(BinaryOp* binary) = 0;
    virtual void VisitUnaryOp(UnaryOp* unary) = 0;
    virtual void VisitConditionalOp(ConditionalOp* cond) = 0;
    virtual void VisitFuncCall(FuncCall* funcCall) = 0;
    virtual void VisitEnumerator(Enumerator* enumer) = 0;
    virtual void VisitIdentifier(Identifier* ident) = 0;
    virtual void VisitObject(Object* obj) = 0;
    virtual void VisitConstant(Constant* cons) = 0;
    virtual void VisitTempVar(TempVar* tempVar) = 0;

    virtual void VisitDeclaration(Declaration* init) = 0;
    virtual void VisitIfStmt(IfStmt* ifStmt) = 0;
    virtual void VisitJumpStmt(JumpStmt* jumpStmt) = 0;
    virtual void VisitReturnStmt(ReturnStmt* returnStmt) = 0;
    virtual void VisitLabelStmt(LabelStmt* labelStmt) = 0;
    virtual void VisitEmptyStmt(EmptyStmt* emptyStmt) = 0;
    virtual void VisitCompoundStmt(CompoundStmt* compStmt) = 0;
    virtual void VisitFuncDef(FuncDef* funcDef) = 0;
private:
    static Parser* parser_;
    std::vector<ASTNode*> roots_; // roots of each block
    std::unique_ptr<llvm::Module> module_;
    std::unique_ptr<llvm::LLVMContext> context_;
    std::unique_ptr<llvm::IRBuilder<>> builder_;
    std::map<std::string,llvm::Value*> NameValues;
//---------------------------------------------
    // The EmitFunc need to be implemented by
    // void EmitFunc(); // A function
    // void EmitDecl(); // global variable
    // Other Emit called by Emit Func() and EmitDecl()

};

#endif