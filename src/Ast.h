#ifndef AST_H
#define AST_H

/* 
 * List type here
 * For example, we have Interger, than there will be a class called Interger
 */
class Expr;
class BinaryOp;
class UnaryOp;
class ConditionalOp;
class FuncCall;
class TempVar;
class Constant;

class Identifier;
class Object;
struct Initializer;
class Declaration;
class Enumerator;

// Statements
class Stmt;
class IfStmt;
class JumpStmt;
class LabelStmt;
class EmptyStmt;
class CompoundStmt;
class FuncDef;
class TranslationUnit;

class ASTNode{
public:
    virtual ~ASTNode() {}

protected:
    ASTNode() {}
};

class Stmt : public ASTNode {
public:
    virtual ~Stmt() {}
protected:
    Stmt() {}
}

/* and so on */

#endif