#include "Parser.h"

    Paser::Parser(){}
    Constant* Paser::ParseConstant(const Token* tok);
    Constant* Paser::ParseFloat(const Token* tok);
    Constant* Paser::ParseInteger(const Token* tok);
    Constant* Parser::ParseCharacter(const Token* tok);
    Constant* Parser::ParseSizeof();
    Constant* Paser::ParseAlignof();
    // Expressions
    Expr* Paser::ParseCastExpr();
    Expr* Paser::ParseMultiplicativeExpr();
    Expr* Paser::ParseAdditiveExpr();
    Expr* Paser::ParseShiftExpr();
    Expr* Paser::ParseRelationalExpr();
    Expr* Paser::ParseEqualityExpr();
    Expr* Paser::ParseBitiwiseAndExpr();
    Expr* Paser::PParseBitwiseXorExpr();
    Expr* Paser::PParseBitwiseOrExpr();
    Expr* Paser::PParseLogicalAndExpr();
    Expr* Paser::PParseLogicalOrExpr();
    Expr* Paser::PParseConditionalExpr();
    Expr* Paser::PParseCommaExpr();
    Expr* Paser::PParseAssignExpr();
    // Declarations
    // Statements
    Stmt* Paser::PParseStmt();
    //CompoundStmt* ParseCompoundStmt(FuncType* funcType=nullptr);
    IfStmt* Paser::PParseIfStmt();
    CompoundStmt* Paser::PParseSwitchStmt();
    CompoundStmt* Paser::PParseWhileStmt();
    CompoundStmt* Paser::PParseDoStmt();
    CompoundStmt* Paser::PParseForStmt();
    JumpStmt* Paser::PParseGotoStmt();
    JumpStmt* Paser::PParseContinueStmt();
    JumpStmt* Paser::PParseBreakStmt();
    ReturnStmt* Paser::PParseReturnStmt();
    CompoundStmt* Paser::PParseLabelStmt(const Token* label);
    CompoundStmt* Paser::PParseCaseStmt();