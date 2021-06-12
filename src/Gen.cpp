#include "Gen.h"

void Generator::Gen(){
    for(int i = 0; i < roots_.size();i++){

    }
    this->module_->dump();
}

#include "Gen.h"

void Generator::Gen(){
    for(int i = 0; i < roots_.size();i++){

    }
    this->module_->dump();
}

void Generator::VisitBinaryOp(BinaryOp* binary){

}
void Generator::VisitUnaryOp(UnaryOp* unary) {

}
void Generator::VisitConditionalOp(ConditionalOp* cond){

}
void Generator::VisitFuncCall(FuncCall* funcCall) {

}
void Generator::VisitEnumerator(Enumerator* enumer) {

}
void Generator::VisitIdentifier(Identifier* ident){

}
void Generator::VisitObject(Object* obj){

}
void Generator::VisitConstant(Constant* cons) {

}
void Generator::VisitTempVar(TempVar* tempVar) {

};
void Generator::VisitDeclaration(Declaration* init) {

}
void Generator::VisitIfStmt(IfStmt* ifStmt) {

}
void Generator::VisitJumpStmt(JumpStmt* jumpStmt) {

}
void Generator::VisitReturnStmt(ReturnStmt* returnStmt) {

}
void Generator::VisitLabelStmt(LabelStmt* labelStmt){

}
void Generator::VisitEmptyStmt(EmptyStmt* emptyStmt) {

}
void Generator::VisitCompoundStmt(CompoundStmt* compStmt){

}
void Generator::VisitFuncDef(FuncDef* funcDef) {

}