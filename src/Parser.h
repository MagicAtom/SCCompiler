#ifndef _PARSER_H_
#define _PARSER_H_
#include "Scanner.h"
#include <string>
#include "Ast.h"
#include "Error.h"



enum class CodeType{
    CHAR16,
    CHAR32,
    UTF8,
    NONE
};

enum {
  // Storage class specifiers
  S_TYPEDEF = 0x01,
  S_EXTERN = 0x02,
  S_STATIC = 0x04,
  S_THREAD = 0x08,
  S_AUTO = 0x10,
  S_REGISTER = 0x20,

  // Type specifier
  T_SIGNED = 0x40,
  T_UNSIGNED = 0x80,
  T_CHAR = 0x100,
  T_SHORT = 0x200,
  T_INT = 0x400,
  T_LONG = 0x800,
  T_VOID = 0x1000,
  T_FLOAT = 0x2000,
  T_DOUBLE = 0x4000,
  T_BOOL = 0x8000,
  T_COMPLEX = 0x10000,
  // T_ATOMIC = 0x20000,
  T_STRUCT_UNION = 0x40000,
  T_ENUM = 0x80000,
  T_TYPEDEF_NAME = 0x100000,

  T_LLONG = 0x2000000,

  // Function specifier
  F_INLINE = 0x4000000,
  F_NORETURN = 0x8000000,
};

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
protected:
    /* 
     * parse different type of expr 
     * for example as following
     * add more if you need it
     */
    // Constant
    Constant* ParseConstant(const Token* tok);
    Constant* ParseFloat(const Token* tok);

    Constant* ParseCharacter(const Token* tok);
    Constant* ParseSizeof();
    Constant* ParseAlignof();
    Constant* ParserInteger(const Token* tok);
    // Expressions
    Expression* ParseCastExpr();
    Expression* ParseMultiplicativeExpr();
    Expression* ParseAdditiveExpr();
    Expression* ParseShiftExpr();
    Expression* ParseRelationalExpr();
    Expression* ParseEqualityExpr();
    Expression* ParseBitiwiseAndExpr();
    Expression* ParseBitwiseXorExpr();
    Expression* ParseBitwiseOrExpr();
    Expression* ParseLogicalAndExpr();
    Expression* ParseLogicalOrExpr();
    Expression* ParseConditionalExpr();
    Expression* ParseCommaExpr();
    Expression* ParseAssignExpr();
    // Declarations
    // Statements
    Stmt* ParseStmt();
    //CompoundStmt* ParseCompoundStmt(FuncType* funcType=nullptr);
    IfStmt* ParseIfStmt();
private:
    TokenSequence* ts_;
    Program* trans_; // root of ast
};

#endif