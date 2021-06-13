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
class CompoundStmt; // 复合类型

class Identifier;
class VarDeclaration;
class Enumerator;

// Stmt
class Stmt;
class IfStmt;
class JumpStmt;
class LabelStmt; // For goto
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
    Expr(Token* tok):token_(tok){ }
    virtual void Accept(Visitor* v);
    virtual ~Expr(){};
    virtual bool IsLVal() = 0;
    virtual void TypeChecking() = 0;
private:
    Token* token_;
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

/* Array, struct, union, enum and so on, but we have enumerator */
class CompoundStmt:public Stmt{
public:
    using StmtList = std::vector<Stmt>;
    StmtList& GetStmts() { return stmtlist_; }
protected:
    CompoundStmt(const StmtList& stmts):stmtlist_(stmts){}
private:
    StmtList stmtlist_;
};

// Expressions
class BinaryOp:public Expr{
public:
    virtual void Accept(Visitor* v) override;
    Expr* GetLHS() {return lhs_;}
    Expr* GetRHS() {return rhs_;}
    unsigned GetOp() { return op_; }
    virtual bool IsLVal() override{

    }
    virtual void TypeChecking() override{

    }
protected:
    BinaryOp(Expr* lhs, Expr* rhs,unsigned op):
        lhs_(lhs),rhs_(rhs),op_(op){}
private:
    Expr* lhs_;
    Expr* rhs_;
    unsigned op_;
};

/* "++" "&" "+" "-" "~" "!" */
class UnaryOp : public Expr{
public:
    virtual void Accept(Visitor* v) override;
    virtual bool IsVal();
    virtual void TypeChecking() override{

    }
protected:
    int op_;
    Expr* operand_;
};

class ConditionalOp:public Expr{
public:
    virtual void Accept(Visitor* v) override;
    virtual bool IsLVal() {return false;}
    virtual void TypeChecking() override;
protected:
    ConditionalOp(Expr* cond,Expr* true_expr,Expr* false_expr):
        cond_(cond),true_expr_(true_expr),false_expr_(false_expr){}
private:
    Expr* cond_;
    Expr* true_expr_;
    Expr* false_expr_;
};
class FuncCall:public Expr{
public:
    virtual void Accept(Visitor* v) override;
    virtual bool IsLVal(){return false;} ;
    void TypeChecking();
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
    bool IsLVal() {return false;}
    void SetGlobal(){global_ = true;}
    virtual void TypeChecking() { }
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
    virtual bool IsLVal() { }
    virtual void TypeChecking() {}
protected:
    Identifier(std::string* name):name_(name){};
private:
    std::string* name_;
};

class VarDeclaration:public Stmt{
public:
    virtual void Accept(Visitor* v) override;
    virtual bool IsLVal() {return false;}
    virtual void TypeChecking() {}
    void SetGlobal(){
        global_ = true;
    }
protected:
    VarDeclaration(Identifier* name,Constant* cst,bool global):
        name_(name),value_(value_),global_(global){}
private:
    Identifier* name_;
    Constant* value_;
    bool global_;
};

class Enumerator:public Identifier{
public:
    virtual void Accept(Visitor* v) override;
protected:
    //Enumerator(Constant* cst):constant_(cst){}
    Constant* constant_;
};


#endif 