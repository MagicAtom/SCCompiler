#include "Gen.h"
#include "Type.h"

void Generator::Gen(){
    for(int i = 0; i < roots_.size();i++){

    }
    this->module_->dump();
}
void Generator::GenExec(){

}
// Util
llvm::Function* Generator::GetTopFunc(){
    return func_stack_.back();
}
llvm::Value* Generator::FindValue(const std::string name) {
    llvm::Value * result = nullptr;
    for (auto it = func_stack_.rbegin(); it != func_stack_.rend(); it++)
    {
        if ((result = (*it)->getValueSymbolTable()->lookup(name)) != nullptr)
        {
            std::cout << "Find " << name << " in " << std::string((*it)->getName()) << std::endl;
            return result;
        }
        else
        {
            std::cout << "Not Find " << name << " in " << std::string((*it)->getName()) << std::endl;
        }
    }
    if ((result = module_->getGlobalVariable(name)) == nullptr)
    {
        throw std::logic_error("[ERROR]Undeclared variable: " + name);
    }
    std::cout << "Find " << name << " in global" << std::endl;
    return result;
}
llvm::Type* Generator::TypeConvert(Type* type) {
    unsigned type_id = type->type_;
    switch(type_id){
        case SCCType::_INT : return llvm::Type::getInt32Ty((*context_));
        case SCCType::_FLOAT : return llvm::Type::getFloatTy(*context_);
        case SCCType::_CHAR : return llvm::Type::getInt8Ty(*context_);
        case SCCType::_DOUBLE : return llvm::Type::getDoubleTy(*context_);
        case SCCType::_VOID: return llvm::Type::getVoidTy(*context_);
        case SCCType::_ARRAY: {
            // Only fix length array is supported
            return llvm::ArrayType::get(TypeConvert(type),type->length_);
        };
        case SCCType::_STRUCT: ;
        default:
            assert(false);
    }
}
llvm::Type* Generator::PtrTypeConvert(Type *type) {
    switch(type->type_) {
        case SCCType::_INT: return llvm::Type::getInt32PtrTy(*context_);
        case SCCType::_FLOAT: return llvm::Type::getFloatPtrTy(*context_);
        case SCCType::_DOUBLE: return llvm::Type::getDoubleTy(*context_);
        case SCCType::_CHAR: return llvm::Type::getInt8PtrTy(*context_);
        case SCCType::_BOOL: return llvm::Type::getInt1PtrTy(*context_);
        default: LOG_ERROR("Pointer type not support");
    }
}
llvm::AllocaInst *Generator::GetInst(llvm::Function *function, llvm::StringRef VarName, llvm::Type *type) {
    llvm::IRBuilder<> tmp(&function->getEntryBlock(), function->getEntryBlock().begin());
    return tmp.CreateAlloca(type, nullptr, VarName);
}
// Visit and gen
llvm::Value* Generator::VisitBinaryOp(BinaryOp* binary) {
    auto lhs = VisitExpr(binary->lhs_);
    auto rhs = VisitExpr(binary->rhs_);

    if(!lhs || !rhs)
        return nullptr;

    bool float_flag = lhs->getType()->isDoubleTy() || rhs->getType()->isDoubleTy();

    unsigned op = binary->GetOp();
    switch(op){
        case Token::EQUAL : return GenAssignment(binary);
        case Token::ADD : return (float_flag ? builder_->CreateFAdd(lhs,rhs,"addftmp") : builder_->CreateAdd(lhs,rhs,"additmp"));
        case Token::SUB : return (float_flag ? builder_->CreateFSub(lhs,rhs,"subftmp") : builder_->CreateSub(lhs,rhs,"subitmp"));
        case Token::MUL : return (float_flag ? builder_->CreateFMul(lhs,rhs,"mulftmp") : builder_->CreateMul(lhs,rhs,"mulitmp"));
        case Token::DIV : return builder_->CreateSDiv(lhs,rhs,"div");
        case Token::EQ : return builder_->CreateICmpEQ(lhs,rhs,"eq");
        case Token::NE : return builder_->CreateICmpNE(lhs,rhs,"neq");
        case Token::LE : return builder_->CreateICmpSLE(lhs,rhs,"le");
        case Token::LESS : return builder_->CreateICmpSLT(lhs,rhs,"lt");
        case Token::GE : return builder_->CreateICmpSGE(lhs,rhs,"ge");
        case Token::GREATER : return builder_->CreateICmpSGT(lhs,rhs,"gt");
        case Token::AND : return builder_->CreateAnd(lhs,rhs,"and");
        case Token::OR : return builder_->CreateOr(lhs,rhs,"or");
        case Token::MOD : return builder_->CreateSRem(lhs,rhs,"mod");
        case Token::XOR : return builder_->CreateXor(lhs,rhs,"xor");
        case Token::DOT : return GenMemberRefOp(binary);
        case Token::COMMA : return GenCommaOp(binary);
    }
}
llvm::Value* Generator::GenMemberRefOp(BinaryOp *binary) {
    llvm::Value* res = nullptr;
    return res;
}
llvm::Value* Generator::GenCommaOp(BinaryOp *binary) {
    llvm::Value* res = nullptr;
    return res;
}
llvm::Value* Generator::VisitUnaryOp(UnaryOp* unary) {
    LOG_INFO("Unary");

    switch(unary->op_) {
        case Token::PREFIX_INC : return GenInc(unary,true);
        case Token::PREFIX_DEC: return  GenInc(unary,true);
        case Token::POSTFIX_INC: return GenInc(unary,false);
        case Token::POSTFIX_DEC: return GenInc(unary,false);
        case Token::PLUS: ;
        case Token::MINUS: ;
        case '~' : ;
        case '!' : ;
        case Token::DEREF: ;
        case Token::CAST: return GenCast(unary) ;
        default: assert(false);
    }
}
llvm::Value* Generator::GenAssignment(BinaryOp *binary) {
    llvm::Value* res = nullptr;
    // TODO:Add array support
    return builder_->CreateStore(VisitExpr(binary->rhs_),FindValue(binary->lhs_->name_));
}
llvm::Value* Generator::GenInc(UnaryOp *unary, bool prefix) {
    llvm::Value* res = nullptr;
    return res;
}
llvm::Value* Generator::GenCast(UnaryOp *unary) {
    llvm::Value* res = nullptr;
    return res;
}
llvm::Value* Generator::VisitConditionalOp(ConditionalOp* cond) {
    LOG_INFO("ConditionOp");
    auto ifstmt = new IfStmt(cond->cond_,cond->true_expr_,cond->false_expr_);
    return VisitIfStmt(ifstmt);
}
llvm::Value* Generator::VisitFuncCall(FuncCall* funcCall) {
    llvm::Function *func = module_->getFunction(*(funcCall->func_->name_));
    if(func == nullptr) {
        std::string error_info = "Function" + *(funcCall->func_->name_) + "not defined.";
        LOG_ERROR(error_info);
    }
    // Iterate
    std::vector<llvm::Value*> args;
    llvm::Function::arg_iterator argIt = func->arg_begin();
    for(auto & arg : *(funcCall->args_)){
        if(argIt->hasNonNullAttr()){
            llvm::Value * addr = FindValue(*(dynamic_cast<Identifier*>(arg)->name_));
            args.push_back(addr); // Pointer or reference
        } else {
            args.push_back(VisitExpr(arg)); // Value
        }
        argIt++;
    }
    llvm::Value *res = builder_->CreateCall(func,args,"calltmp");
    return res;
}
llvm::Value* Generator::VisitEnumerator(Enumerator* enumer) {

}
llvm::Value* Generator::VisitIdentifier(Identifier* ident) {
    return new llvm::LoadInst(FindValue(*ident->name_),"tmp",false,builder_->GetInsertBlock());
}
llvm::Value* Generator::VisitConstant(Constant* cons) {
    LOG_INFO("Get Constant");
    return new llvm::LoadInst(FindValue(cons->name_));
}
llvm::Value* Generator::VisitTempVar(TempVar* tempVar) {
    llvm::Value* res;
    return res;
}
llvm::Value* Generator::VisitDeclaration(Declaration *decl){
    llvm::Value* alloc = nullptr;
    llvm::Type* type;
    for(const auto & id : *(decl->idents_)){
        if(decl->type_->type_ == SCCType::_ARRAY){
            // Array not supported yet.
        }
        type = TypeConvert(decl->type_);
        if(decl->global_){
            alloc = new llvm::GlobalVariable(*module_,type,decl->isConst_,llvm::GlobalValue::InternalLinkage, InitValue(type),*id->name_);
        } else {
            alloc = GetInst(GetTopFunc(),*id->name_,type);
        }
    }
    return alloc;
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
    llvm::Value* res = nullptr;
    if(returnStmt->expr_ != nullptr) {
        VisitExpr(returnStmt->expr_);
    } else {
        builder_->CreateRetVoid();
    }
    return res;
}
llvm::Value* Generator::VisitLabelStmt(LabelStmt* labelStmt) {
    return nullptr;
}
llvm::Value* Generator::VisitEmptyStmt(EmptyStmt* emptyStmt) {
    return nullptr;
}
llvm::Value* Generator::VisitCompoundStmt(CompoundStmt* compStmt) {
    llvm::Value *res = nullptr;
    for(auto & stmt : compStmt->stmtlist_) {
        res = VisitStmt(&stmt);
    }
    return res;
}
llvm::Value* Generator::VisitFuncDecl(FuncDecl* funcDecl) {
    LOG_INFO("Function Declaration");
    // Prototype
    std::vector<llvm::Type*> argTypes;
    for(const auto & argType: *(funcDecl->params_)) {
        if(argType->isVar_){
            argTypes.insert(argTypes.end(),argType->idents_->size(), PtrTypeConvert(argType->type_));
        }
        else {
            argTypes.insert(argTypes.end(),argType->idents_->size(), TypeConvert(argType->type_));
        }
    }
    llvm::FunctionType *FT = llvm::FunctionType::get(TypeConvert(funcDecl->type_),argTypes,false);
    llvm::Function* function = llvm::Function::Create(FT,llvm::GlobalValue::InternalLinkage,*funcDecl->ident_->name_,module_.get());
    func_stack_.push_back(function);

    llvm::BasicBlock * newBlock = llvm::BasicBlock::Create(*context_,"entrypoint",function,nullptr);
    builder_->SetInsertPoint(newBlock);

    llvm::Function::arg_iterator argIt = function->arg_begin();
    int index = 0;
    for(const auto & args: *(funcDecl->params_)) {
        for(const auto arg : *(args->idents_)) {
            llvm::Value * alloc = nullptr;
            if(args->isVar_){
                function->addAttribute(index,llvm::Attribute::NonNull);
                alloc = builder_->CreateGEP(argIt++,builder_->getInt32(0),*arg->name_);
            } else {
                alloc = GetInst(function,*arg->name_,TypeConvert(args->type_));
            }
            index++;
        }
    }
    llvm::Value *res = nullptr;
    if(funcDecl->type_->type_ != SCCType::_VOID){
        res = GetInst(function,*funcDecl->ident_->name_,TypeConvert(funcDecl->type_));
    }
    VisitCompoundStmt(funcDecl->body_); // Body
    VisitReturnStmt(new ReturnStmt(funcDecl->retexpr_));
    // builder_->CreateRet(VisitReturnStmt(new ReturnStmt(funcDecl->retexpr_)));
    func_stack_.pop_back();
    builder_->SetInsertPoint(&(GetTopFunc())->getBasicBlockList().back());
    return function;
}
llvm::Value* Generator::VisitExpr(Expr* expr){
    expr->Accept(this);
}
llvm::Value* Generator::VisitStmt(Stmt* stmt){
    stmt->Accept(this);
}