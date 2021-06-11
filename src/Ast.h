#ifndef SCC_AST_H
#define SCC_AST_H

// Forward Definition
class Generator;
class Visitor; 

// Expressions
class Expr;
class BinaryOp;
class UnaryOp;
class ConditionalOp;
class FuncCall;
class TempVar;
class Constant;

class Indentifier;
class Initializer;
class Declaration;
class Enumerator;

// Stmt
class Stmt;
class IfStmt;
class JumpStmt;
class LabelStmt;
class EmptyStmt;
class FuncDef;

class ASTNode{
public:
    virtual ~ASTNode();
    virtual void Accept(Visitor* v) = 0; // Visitor Pattern
protected:
    ASTNode() {}
};


#endif 