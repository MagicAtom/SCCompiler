#include "Gen.h"

void Generator::Gen(){
    for(int i = 0; i < roots_.size();i++){

    }
    this->module_->dump();
}

llvm::Value* VisitBinaryOp(BinaryOp* binary) {

}
llvm::Value* VisitUnaryOp(UnaryOp* unary) {

};
llvm::Value* VisitConditionalOp(ConditionalOp* cond) {

}
llvm::Value* VisitFuncCall(FuncCall* funcCall) {

}
llvm::Value* VisitEnumerator(Enumerator* enumer) {

}
llvm::Value* VisitIdentifier(Identifier* ident) {

}
llvm::Value* VisitObject(Object* obj) {

}
llvm::Value* VisitConstant(Constant* cons) {

}
llvm::Value* VisitTempVar(TempVar* tempVar) {

}

llvm::Value* VisitDeclaration(Declaration* init) {

}
llvm::Value* VisitIfStmt(IfStmt* ifStmt) {

}
llvm::Value* VisitJumpStmt(JumpStmt* jumpStmt) {

}
llvm::Value* VisitReturnStmt(ReturnStmt* returnStmt) {

}
llvm::Value* VisitLabelStmt(LabelStmt* labelStmt) {

}
llvm::Value* VisitEmptyStmt(EmptyStmt* emptyStmt) {

}
llvm::Value* VisitCompoundStmt(CompoundStmt* compStmt) {

}
llvm::Value* VisitFuncDef(FuncDef* funcDef) {

}