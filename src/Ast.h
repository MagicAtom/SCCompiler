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

class Identifier;
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

// Statemnts
class Stmt : public ASTNode {
    
};

class IfStmt : public Stmt{

};

class JumpStmt : public Stmt {

};

class LabelStmt:public Stmt{

};

class EmptyStmt:public Stmt{

};

class FuncDef:public Stmt{

};

// Expressions
class Expr:public Stmt{

};

class BinaryOp:public Expr{

};

class UnaryOp : public Expr{

};

class ConditionalOp:public Expr{

};
class FuncCall:public Expr{

};
class TempVar:public Expr{

};
class Constant:public Expr{

};

class Identifier:public Expr{

};
class Initializer:public Expr{

};
class Declaration:public Expr{

};
class Enumerator:public Expr{

};


#endif 