#include "Ast.h"
#include "Visitor.h"


void BinaryOp::Accept(Visitor *v) {
    v->VisitBinaryOp(this);
};

void UnaryOp::Accept(Visitor *v) {
    v->VisitUnaryOp(this);
};
void ConditionalOp::Accept(Visitor *v) {
    v->VisitConditionalOp(this);
}
void FuncCall::Accept(Visitor *v) {
    v->VisitFuncCall(this);
};
void TempVar::Accept(Visitor *v) {
    v->VisitTempVar(this);
}
void Constant::Accept(Visitor *v) {
    v->VisitConstant(this);
}
void Identifier::Accept(Visitor* v){
    v->VisitIdentifier(this);
}

void Declaration::Accept(Visitor *v) {
    v->VisitDeclaration(this);
};
void Enumerator::Accept(Visitor *v) {
    v->VisitEnumerator(this);
}
void IfStmt::Accept(Visitor *v) {
    v->VisitIfStmt(this);
};
void JumpStmt::Accept(Visitor *v) {
    v->VisitJumpStmt(this);
}
void LabelStmt::Accept(Visitor *v) {
    v->VisitLabelStmt(this);
}
void EmptyStmt::Accept(Visitor *v) {
    v->VisitEmptyStmt(this);
};
void FuncDef::Accept(Visitor *v) {
    v->VisitFuncDef(this);
}
