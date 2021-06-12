#ifndef SCC_AST_H
#define SCC_AST_H

#include "Core.h"
#include <string>
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
class Object;
class Declaration;
class Enumerator;

// Stmt
class Stmt;
class IfStmt;
class JumpStmt;
class LabelStmt;
class EmptyStmt;
class ReturnStmt;
using ParamList = std::vector<Expr>;

class ASTNode{
public:
    virtual ~ASTNode();
    virtual void Accept(Visitor* v) = 0; // Visitor Pattern
protected:
    ASTNode() {}
};

// Statemnts
class Stmt : public ASTNode {
public:
    virtual void Accept(Visitor* v);
};

class IfStmt : public Stmt{
public:
    ~IfStmt(){
        delete cond_;
        delete then_;
        delete else_;
    };
    void Accept(Visitor* v);
protected:
    IfStmt(Expr* cond,Stmt* then,Stmt* els):cond_(cond),then_(then),else_(els){}
private:
    Expr* cond_;
    Stmt* then_;
    Stmt* else_;
};

class Expr:public Stmt{
public:
    virtual void Accept(Visitor* v);
    virtual ~Expr(){};
};

class JumpStmt : public Stmt {
public:
    virtual void Accept(Visitor* v) override;
    virtual ~JumpStmt(){};
protected:
    JumpStmt(LabelStmt* label):label_(label) {}
private:
    LabelStmt* label_;
};

class LabelStmt:public Stmt{
public:
    void Accept(Visitor* v);
    virtual ~LabelStmt(){}
protected:
    LabelStmt(int label):tag_(label){}
private:
    int tag_;
};

class EmptyStmt:public Stmt{
public:
    virtual void Accept(Visitor* v) override;
    virtual ~EmptyStmt();
protected:
    EmptyStmt(){}
};

class ReturnStmt:public Stmt{
public:
    virtual ~ReturnStmt(){};
    virtual void Accept(Visitor* v) override;
protected:
    ReturnStmt(Expr* expr):expr_(expr){}
private:
    Expr* expr_;
};

class FuncDef:public Stmt{
public:
    virtual void Accept(Visitor* v) override;
protected:
    FuncDef(Identifier* ident,LabelStmt* label):idt_(ident),label_(label){}
private:
    LabelStmt* label_;
    Identifier* idt_;
};

// Expressions
class BinaryOp:public Expr{
public:
    virtual void Accept(Visitor* v) override;
protected:
    BinaryOp(){}
private:
    Expr* lhs_,rhs_;
    int op_;
};

class UnaryOp : public Expr{
public:
    virtual void Accept(Visitor* v) override;
protected:
    int op_;
    Expr* operand_;
};

class ConditionalOp:public Expr{
public:
    virtual void Accept(Visitor* v) override;
private:
};
class FuncCall:public Expr{
public:
    virtual void Accept(Visitor* v) override;
protected:
    FuncCall(Identifier* func,LabelStmt* label):func_(func),label_(label){}
private:
    Identifier* func_;
    LabelStmt* label_;
};
class TempVar:public Expr{
public:
    virtual void Accept(Visitor* v) override;
    bool IsLVal(){return true;}
protected:
    TempVar(){

    }
private:
    int tag_;
};
class Constant:public Expr{
public:
    virtual void Accept(Visitor* v) override;
    void SetGlobal(){global_ = true;}
protected:
    Constant(Type* type){

    }
    union{
        int i_;
        double ft_;
        bool tf_;
        char c_;
    };
    Identifier *name;
    bool global_;
    Type * type_;
};

class Identifier:public Expr{
public:
    virtual void Accept(Visitor* v) override;
protected:
    Identifier(std::string* name):name_(name){};
private:
    std::string* name_;
};

class Declaration:public Expr{
public:
    virtual void Accept(Visitor* v) override;
private:
};

class Enumerator:public Identifier{
public:
    virtual  void Accept(Visitor* v) override;
protected:
    //Enumerator(Constant* cst):constant_(cst){}
    Constant* constant_;
};


#endif 