#include "Parser.h"

    Parser::Parser(){}
    Constant* Parser::ParseConstant(const Token* tok){
        assert(tok->IsConstant());

        if(tok->tag_ == Token::I_CONSTANT){
            return ParserInteger(tok);
        }else if(tok->tag_ == Token::I_CONSTANT){
            return ParseCharacter(tok);
        }else{
            return ParseFloat(tok);
        }
    }

    Constant* Parser::ParserInteger(const Token* tok){
        const auto& str = tok->str_;
        size_t end = 0;
        long val = 0;
        try{
            val = stoull(str,&end,0);
        }catch(const std::out_of_range& oor){
            Error(tok, "integer out of range");
        }

        int tag = 0;
        for(;str[end];end++){
            if(str[end] == 'u' || str [end] == 'U'){
                if(tag& T_UNSIGNED)
                    Error(tok, "invalid suffix");
                tag |= T_UNSIGNED;
            }else{
                if((tag & T_LONG) || (tag & T_LLONG))
                    Error(tok,"invalid suffix");
                else if(str[end+1] == "l" || str[end + 1] == "L"){
                    tag |= T_LLONG;
                    ++end;
                }else{
                    tag |= T_LONG;
                }
            }
        }
    }

    Constant* Parser::ParseFloat(const Token* tok){
        const auto& str = tok->str_;
        size_t end = 0;
        double value = 0.0;
        try{
            value = stod(str, &end);
        }catch(const std::out_of_range& out_range){
            Error(tok, "float overflow");
        }
        int tag = T_DOUBLE;

    }
    Constant* Parser::ParseCharacter(const Token* tok){
        int val;
        auto in_char = Scanner(tok).ScanChar(val);
        int tag;

        switch(in_char){
        case CodeType::NONE:
            val = char(val);
            tag = T_INT;
            break;
        case CodeType::CHAR16:
            val = (char16_t)val;
            tag = T_UNSIGNED | T_SHORT;
            break;
        case CodeType::CHAR32:
            tag = T_UNSIGNED | T_INT;
            break;
        default: assert(false);
        }

        return Constant::New(tok, tag, val);

    }
    Constant* Parser::ParseSizeof(){
        Type* type;
        auto token = ts_->Next();
        if(token->tag_ == '(' && ts_->Peek()){
            type = Type::Type(SCCType::_USER_DEFINED);
            ts_->Expect(')');
        }else{
            ts_->Back();
        }

        long val = type->var_;
        return Constant::New(tok, T_UNSIGNED | T_LONG, val);
    }
    Constant* Parser::ParseAlignof(){
        ts_->Expect('(');
        auto tok = ts_->Peek();
        auto type = Type(SCCType::_CHAR);
        ts_->Expect(')');

        long val = type.var_;
        return Constant::New(tok, T_UNSIGNED | T_LONG, val);
    }
    // Expressions
    Expression* Parser::ParseCastExpr(){
        auto tok = ts_->Next();
        if(tok->tag_ == '(' && ts_->Peek()){
            auto type = Type::Type(SCCType::_STRUCT);
            ts_->Expect(')');

            if(ts_->Test("{")){
                auto next = ParseLabelStmt( tok);
                return Expression::Expression(tok);
            }
            ts_->Back();
            {
            auto tok = ts_->Next();
            switch (tok->tag_) {
            case Token::ALIGNOF: return ParseAlignof();
            case Token::SIZEOF: return ParseSizeof();
            }
        }
    }
    Expression* Parser::ParseMultiplicativeExpr(){
        Token* tok = ts_->Next();
        auto mulval = ParseCastExpr();
        while(tok->tag_=='*' || tok->tag_=='/' ||tok ->tag_ == '%'){
            tok = ts_.Next();
        }
        ts_->Back();
        return mulval;
    }
    Expression* Parser::ParseAdditiveExpr(){
        auto addval = ParseMultiplicativeExpr();
        auto token = ts_->Next();
        while(token ->tag_ == '+' || Token->tag_ == '-'){
            tok = ts_->Next()
        }
        ts_->Back();
        return addval;
    }
    Expression* Parser::ParseShiftExpr(){
    auto shiftval = ParseAdditiveExpr();
    auto token = ts_.Next();
    while (token->tag_ == Token::LEFT || token->tag_ == Token::RIGHT) {
        auto reset = ParseAdditiveExpr();

        tok = ts_.Next();
    }

        ts_.PutBack();
        return shiftval;
    }
    Expression* Parser::ParseRelationalExpr(){
        auto reval = ParseAdditiveExpr();
        auto token = ts_->Next();
        while(token->tag_ == Token::LEFT || token->tag_ == Token:: RIGHT){
            auto loc = ParseAdditiveExpr();
            token = ts_.Next();
        }
    }
    Expression* Parser::ParseEqualityExpr(){
        auto equaltok = ParseRelationalExpr();
        Token* token = ts_.Next();

        while(tok->tag_ == Token::EQ){
            auto loc = ParseRelationalExpr();

            equaltok = ts_.Next();
        }

        ts_->Back();
        retrun equaltok;
    }
    Expression* Parser::ParseBitiwiseAndExpr(){
        auto bitwise = ParseEqualityExpr();
        auto token = ts_.Peek();
        while (ts_->Try('&')) {
        auto loc = ParseEqualityExpr();

        tok = ts_.Peek();
  }

        return bitwise;    
    }
    Expression* Parser::ParseBitwiseXorExpr(){
        auto Xorval = ParseBitiwiseAndExpr();
        auto token = ts_->Peek();
        while (ts_->Try('^')) {
        auto loc = ParseBitiwiseAndExpr();

        token = ts_.Peek();
        }

        return lhs;
    }
    Expression* Parser::ParseBitwiseOrExpr(){
        auto bitorval = ParseBitwiseXorExpr();
        auto token = ts_.Peek();
        while (ts_.Try('|')) {
            auto loc = ParseBitwiseXorExpr();

            token = ts_.Peek();
        }

        return bitorval;        
    }
    Expression* Parser::ParseLogicalAndExpr(){
        auto bitandval = ParseBitwiseOrExpr();
        auto token = ts_.Peek();
        while (ts_.Try(Token::LOGICAL_AND)) {
            auto loc = ParseBitwiseOrExpr();

            token = ts_.Peek();
        }

        return bitandval;
    }
    Expression* Parser::ParseLogicalOrExpr(){
        auto bitorval = ParseLogicalAndExpr();
        auto token = ts_.Peek();
        while (ts_.Try(Token::LOGICAL_OR)) {
            auto loc = ParseLogicalAndExpr();

            token = ts_.Peek();
  }

        return bitorval;
    }
    Expression* Parser::ParseConditionalExpr(){
    auto condval = ParseLogicalOrExpr();
    auto token = ts_.Peek();
    if (ts_.Try('?')) {
        // Non-standard GNU extension
        // a ?: b equals a ? a: c
        auto Rexpr = ts_.Test(':') ? condval: ParseExpr();
        ts_.Expect(':');
        auto Fexpr = ParseConditionalExpr();

        return condval;
  }

        return condval;
    }
    Expression* Parser::ParseCommaExpr(){
    Expression* assignval = ParseConditionalExpr();
    Expression* loc;

  auto token = ts_.Next();
  switch (token->tag_) {
    case Token::MUL_ASSIGN:
        loc = ParseAssignExpr();
        break;

    case Token::DIV_ASSIGN:
        loc = ParseAssignExpr();
        break;

    case Token::MOD_ASSIGN:
        loc = ParseAssignExpr();
        break;

    case Token::ADD_ASSIGN:
        loc = ParseAssignExpr();
        break;
    default:
        ts_->PutBack();
        return assignval; // Could be constant
  }

        return assignval;
}
    // Declarations


    // Statements
    Stmt* Parser::ParseStmt(){
    case Token::ATTRIBUTE:
    TryAttributeSpecList();
    case ';':
        return EmptyStmt::New();
    case '{':
        return ParseCompoundStmt();
    case Token::IF:
        return ParseIfStmt();
    case Token::SWITCH:
        return ParseSwitchStmt();
    case Token::WHILE:
        return ParseWhileStmt();
    case Token::DO:
        return ParseDoStmt();
    case Token::FOR:
        return ParseForStmt();
    case Token::GOTO:
        return ParseGotoStmt();
    case Token::CONTINUE:
        return ParseContinueStmt();
    case Token::BREAK:
        return ParseBreakStmt();
    case Token::RETURN:
        return ParseReturnStmt();
    }
    ts_->Back();
    ts_->Expect(';');

    return expr;
}

    IfStmt* Parser::ParseIfStmt(){
        ts_.Expect('(');
        auto token = ts_.Peek();
        auto cond = ParseExpr();
        if (!cond->Type()->IsScalar()) {
            Error(token, "expect scalar");
        }
        ts_.Expect(')');

        auto then = ParseStmt();
        Stmt* els = nullptr;
        if (ts_.Try(Token::ELSE))
            els = ParseStmt();

        return IfStmt::New(cond, then, els);       
    }