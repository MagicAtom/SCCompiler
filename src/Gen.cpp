#include "Gen.h"

void Generator::Gen(){
    for(int i = 0; i < roots_.size();i++){

    }
    this->module_->dump();
}

void Generator::GenExec(){

}

llvm::Value* Generator::VisitBinaryOp(BinaryOp* binary) {
    auto lhs = VisitExpr(binary->GetLHS());
    auto rhs = VisitExpr(binary->GetRHS());

    if(!lhs || !rhs)
        return nullptr;

    switch(binary->GetOp()){

    }
}
llvm::Value* Generator::VisitUnaryOp(UnaryOp* unary) {

};
llvm::Value* Generator::VisitConditionalOp(ConditionalOp* cond) {

}
llvm::Value* Generator::VisitFuncCall(FuncCall* funcCall) {

}
llvm::Value* Generator::VisitEnumerator(Enumerator* enumer) {

}
llvm::Value* Generator::VisitIdentifier(Identifier* ident) {

}
llvm::Value* Generator::VisitObject(Object* obj) {

}
llvm::Value* Generator::VisitConstant(Constant* cons) {

}
llvm::Value* Generator::VisitTempVar(TempVar* tempVar) {

}

llvm::Value* Generator::VisitVarDeclaration(Declaration* init) {

}
llvm::Value* Generator::VisitIfStmt(IfStmt* ifStmt) {

}
llvm::Value* Generator::VisitJumpStmt(JumpStmt* jumpStmt) {

}
llvm::Value* Generator::VisitReturnStmt(ReturnStmt* returnStmt) {

}
llvm::Value* Generator::VisitLabelStmt(LabelStmt* labelStmt) {

}
llvm::Value* Generator::VisitEmptyStmt(EmptyStmt* emptyStmt) {

}
llvm::Value* Generator::VisitCompoundStmt(CompoundStmt* compStmt) {

}
llvm::Value* Generator::VisitFuncDef(FuncDef* funcDef) {

}
llvm::Value* Generator::VisitExpr(Expr* expr){

}