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

    bool float_flag = lhs->getType()->isDoubleTy() || rhs->getType()->isDoubleTy();

    unsigned op = binary->GetOp();
    switch(op){
        // TODO:: ASSIGMENT is different from below
        case BinaryOperator::_ASSIGNMENT:{

        }
        case BinaryOperator::_ADD: return (float_flag ? builder_->CreateFAdd(lhs,rhs,"ADD") : builder_->CreateAdd(lhs,rhs,"ADDI"));
        case BinaryOperator::_MINUS: return (float_flag ? builder_->CreateFSub(lhs,rhs,"SUB") : builder_->CreateSub(lhs,rhs,"SUBI"));
        case BinaryOperator::_MUL: return (float_flag ? builder_->CreateFMul(lhs,rhs,"MUL") : builder_->CreateMul(lhs,rhs,"MULI"));
        case BinaryOperator::_DIV: return builder_->CreateSDiv(lhs,rhs,"DIV");
        case BinaryOperator::_EQ: return builder_->CreateICmpEQ(lhs,rhs,"EQ");
        case BinaryOperator::_NEQ: return builder_->CreateICmpNE(lhs,rhs,"NEQ");
        case BinaryOperator::_LE: return builder_->CreateICmpSLE(lhs,rhs,"LE");
        case BinaryOperator::_LT: return builder_->CreateICmpSLT(lhs,rhs,"LT");
        case BinaryOperator::_GE: return builder_->CreateICmpSGE(lhs,rhs,"GE");
        case BinaryOperator::_GT: return builder_->CreateICmpSGT(lhs,rhs,"GT");
        case BinaryOperator::_AND: return builder_->CreateAnd(lhs,rhs,"AND");
        case BinaryOperator::_OR: return builder_->CreateOr(lhs,rhs,"OR");
        case BinaryOperator::_MOD: return builder_->CreateSRem(lhs,rhs,"MOD");
        case BinaryOperator::_XOR: return builder_->CreateXor(lhs,rhs,"XOR");
        // TODO:: Implement dot, paren operator.
    }
}

llvm::Value* Generator::VisitUnaryOp(UnaryOp* unary) {
    LOG_INFO("unary");
};
llvm::Value* Generator::VisitConditionalOp(ConditionalOp* cond) {
    LOG_INFO("condition");

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
    // TODO: Label should be add here
    LOG_INFO("IF_STMT");
    llvm::Value *cond_value = this->VisitExpr(ifStmt->cond_);
    cond_value = builder_->CreateICmpNE(cond_value,llvm::ConstantInt::get(llvm::Type::getInt1Ty(*context_),0,true));

    llvm::Function *top_func = builder_->GetInsertBlock()->getParent();
    llvm::BasicBlock* then_expr = llvm::BasicBlock::Create(*context_,"then",top_func);
    llvm::BasicBlock* else_expr = llvm::BasicBlock::Create(*context_,"else",top_func);
    llvm::BasicBlock* merge = llvm::BasicBlock::Create(*context_,"merge",top_func);
    auto if_stmt = builder_->CreateCondBr(cond_value,then_expr,else_expr);

    then_expr = builder_->GetInsertBlock();
    builder_->SetInsertPoint(then_expr);
    auto then_value = VisitExpr(ifStmt->cond_);
    builder_->CreateBr(merge);

    builder_->SetInsertPoint(else_expr);
    if(ifStmt->else_ != nullptr)
        auto else_value = VisitStmt(ifStmt->else_);
    builder_->SetInsertPoint(merge);

    return if_stmt;
}
llvm::Value* Generator::VisitJumpStmt(JumpStmt* jumpStmt) {
    // TODO: label should be add here
    llvm::Value* res = nullptr;
    if(basic_blocks_[jumpStmt->label_tag] == nullptr){
        // create new basic block
        basic_blocks_[jumpStmt->label_tag] = llvm::BasicBlock::Create(*context_,"Label"+to_string(jumpStmt->label_tag),GetTopFunc());
    }
    res = builder_->CreateBr(basic_blocks_[jumpStmt->label_tag]);
    return res;
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
llvm::Value* Generator::VisitStmt(Stmt* stmt){

}
llvm::Function* Generator::GetTopFunc(){
    return func_stack_.back();
}
