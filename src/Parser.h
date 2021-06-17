#ifndef PARSER_H
#define PARSER_H

#include "Ast.h"
#include "Scanner.h"

// Parser gen Ast
class Parser {
public:
    Parser(){
        
    }
    Parser(TokenSequence* ts):ts_(ts){

    }
    ~Parser() {}

    void Parse(); // this is main function
    void Translate();
    Program* GetASTRoot() { return trans_;}
private:
    /* 
     * parse different type of expr 
     * for example as following
     * add more if you need it
     */
    // Constant
    Constant* ParseConstant(const Token* tok);
    Constant* ParseFloat(const Token* tok);
    Constant* ParseInteger(const Token* tok);
    Constant* ParseCharacter(const Token* tok);
    Constant* ParseSizeof();
    Constant* ParseAlignof();
    // Expressions
    Expr* ParseCastExpr();
    Expr* ParseMultiplicativeExpr();
    Expr* ParseAdditiveExpr();
    Expr* ParseShiftExpr();
    Expr* ParseRelationalExpr();
    Expr* ParseEqualityExpr();
    Expr* ParseBitiwiseAndExpr();
    Expr* ParseBitwiseXorExpr();
    Expr* ParseBitwiseOrExpr();
    Expr* ParseLogicalAndExpr();
    Expr* ParseLogicalOrExpr();
    Expr* ParseConditionalExpr();
    Expr* ParseCommaExpr();
    Expr* ParseAssignExpr();
    // Declarations
    // Statements
    Stmt* ParseStmt();
    //CompoundStmt* ParseCompoundStmt(FuncType* funcType=nullptr);
    IfStmt* ParseIfStmt();
    CompoundStmt* ParseSwitchStmt();
    CompoundStmt* ParseWhileStmt();
    CompoundStmt* ParseDoStmt();
    CompoundStmt* ParseForStmt();
    JumpStmt* ParseGotoStmt();
    JumpStmt* ParseContinueStmt();
    JumpStmt* ParseBreakStmt();
    ReturnStmt* ParseReturnStmt();
    CompoundStmt* ParseLabelStmt(const Token* label);
    CompoundStmt* ParseCaseStmt();
private:
    TokenSequence* ts_;
    Program* trans_; // root of ast
};

#endif