#ifndef SCC_GEN_H
#define SCC_GEN_H

#include "Ast.h"
#include "Visitor.h"
#include "Type.h"
#include <iostream>
#include <memory>
#include <map>
#include <utility>

class Parser;
class Token;

class Generator:public Visitor{
public:
    inline Generator(){
        context_ = std::make_unique<llvm::LLVMContext>();
        module_ = std::make_unique<llvm::Module>("SCComplier",*context_);
        builder_ = std::make_unique<llvm::IRBuilder<>>(*context_);
    }
    inline Generator(Program* root):root_(root){
        context_ = std::make_unique<llvm::LLVMContext>();
        module_ = std::make_unique<llvm::Module>("SCComplier",*context_);
        builder_ = std::make_unique<llvm::IRBuilder<>>(*context_);
    }
    void GenIR();
    void GenExec();
    void GenObjCode(const std::string filename);
public: // visitor
    virtual llvm::Value* VisitASTNode(ASTNode* node) override;
    virtual llvm::Value* VisitBinaryOp(BinaryOp* binary) override;
    virtual llvm::Value* VisitUnaryOp(UnaryOp* unary) override;
    virtual llvm::Value* VisitConditionalOp(ConditionalOp* cond) override;
    virtual llvm::Value* VisitFuncCall(FuncCall* funcCall) override;
    virtual llvm::Value* VisitEnumerator(Enumerator* enumer) override;
    virtual llvm::Value* VisitIdentifier(Identifier* ident) override;
    virtual llvm::Value* VisitConstant(Constant* cons) override;
    virtual llvm::Value* VisitTempVar(TempVar* tempVar) override;

    virtual llvm::Value* VisitIfStmt(IfStmt* ifStmt) override;
    virtual llvm::Value* VisitJumpStmt(JumpStmt* jumpStmt) override;
    virtual llvm::Value* VisitReturnStmt(ReturnStmt* returnStmt) override;
    virtual llvm::Value* VisitLabelStmt(LabelStmt* labelStmt) override;
    virtual llvm::Value* VisitEmptyStmt(EmptyStmt* emptyStmt) override;
    virtual llvm::Value* VisitObject(Object* object) override { return nullptr;}
    virtual llvm::Value* VisitCompoundStmt(CompoundStmt* compStmt) override;
    virtual llvm::Value* VisitFuncDecl(FuncDecl* funcDecl) override;
    virtual llvm::Value* VisitDeclaration(Declaration* decl) override;
    virtual void         VisitProgram(Program* program) override;
    virtual llvm::Value* VisitParameter(Parameter* para) {return nullptr;}
private:
    // TODO: Visual the AST here when gen IR
private:
    llvm::Function* GetTopFunc();
    llvm::AllocaInst * GetInst(llvm::Function * function,llvm::StringRef VarName,llvm::Type* type);
    llvm::Value* FindValue(const std::string name);
    llvm::Type* TypeConvert(Type* type);
    llvm::Type* PtrTypeConvert(Type* type);
    llvm::Constant* InitValue(Type* type);

    llvm::Value* VisitExpr(Expr* expr);
    llvm::Value* VisitStmt(Stmt* stmt);
    llvm::Value* GenAssignment(BinaryOp* binary);    // Binary Operator
    llvm::Value* GenMemberRefOp(BinaryOp* binary);
    llvm::Value* GenCommaOp(BinaryOp* binary);
    llvm::Value* GenInc(UnaryOp* unary,bool prefix); // Unary Op
    llvm::Value* GenCast(UnaryOp* unary);

private:
    Program* root_;
    std::unique_ptr<llvm::Module> module_;
    std::unique_ptr<llvm::LLVMContext> context_;
    std::unique_ptr<llvm::IRBuilder<>> builder_;
    std::map<std::string,llvm::Value*> name_values_;
    std::vector<llvm::Function*> func_stack_;
    std::vector<llvm::BasicBlock*> basic_blocks_;
    //---------------------------------------------
    // Below is to set register on ourselves.
    // void EmitFunc(); // A function
    // void EmitDecl(); // global variable
    // Other Emit called by Emit Func() and EmitDecl()

};

#endif