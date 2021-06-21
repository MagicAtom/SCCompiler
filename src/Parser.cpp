#include "Parser.h"

    Parser::Parser(){}
    Constant* Parser::ParseConstant(const Token* tok){}
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
    Constant* Parser::ParseInteger(const Token* tok){}
    Constant* Parser::ParseCharacter(const Token* tok){}
    Constant* Parser::ParseSizeof(){}
    Constant* Parser::ParseAlignof(){}
    // Expressions
    Expr* Parser::ParseCastExpr(){}
    Expr* Parser::ParseMultiplicativeExpr(){}
    Expr* Parser::ParseAdditiveExpr(){}
    Expr* Parser::ParseShiftExpr(){}
    Expr* Parser::ParseRelationalExpr(){}
    Expr* Parser::ParseEqualityExpr(){}
    Expr* Parser::ParseBitiwiseAndExpr(){}
    Expr* Parser::ParseBitwiseXorExpr(){}
    Expr* Parser::ParseBitwiseOrExpr(){}
    Expr* Parser::ParseLogicalAndExpr(){}
    Expr* Parser::ParseLogicalOrExpr(){}
    Expr* Parser::ParseConditionalExpr(){}
    Expr* Parser::ParseCommaExpr(){}
    Expr* Parser::ParseAssignExpr(){}
    // Declarations


    // Statements
    Stmt* Parser::ParseStmt(){}

    IfStmt* Parser::ParseIfStmt(){}
    CompoundStmt* Parser::ParseSwitchStmt(){}
    CompoundStmt* Parser::ParseWhileStmt(){}
    CompoundStmt* Parser::ParseDoStmt(){}
    CompoundStmt* Parser::ParseForStmt(){}
    JumpStmt* Parser::ParseGotoStmt(){}
    JumpStmt* Parser::ParseContinueStmt(){}
    JumpStmt* Parser::ParseBreakStmt(){}
    ReturnStmt* Parser::ParseReturnStmt(){}
    CompoundStmt* Parser::ParseLabelStmt(const Token* label){}
    CompoundStmt* Parser::ParseCaseStmt(){}