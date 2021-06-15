#ifndef SCC_AST_H
#define SCC_AST_H

#include "Token.h"
#include "Visitor.h"
#include <string>
#include <iostream>

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
class Object;
class Identifier;
class Declaration;
class Enumerator;

// Stmt
class FuncDecl;
class Stmt;
class IfStmt;
class JumpStmt;
class LabelStmt; // For goto
class EmptyStmt;
class ReturnStmt;
using ParamList = std::vector<Object*>;

typedef struct Initializer {
    Initializer(llvm::Type* type,Expr* expr):type_(type),expr_(expr){}
    Expr* expr_;
    llvm::Type* type_;
}Initializer;

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
    friend class Generator;
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
    friend class Generator;
public:
    Expr() {}
    Expr(Token* tok):token_(tok){ }
    void Accept(Visitor* v) override;
    virtual ~Expr(){};
    virtual bool IsLVal() = 0;
    virtual void TypeChecking() = 0;
private:
    Token* token_;
    std::string name_;
};

class JumpStmt : public Stmt {
    friend class Generator;
public:
    void Accept(Visitor* v) override;
    virtual ~JumpStmt(){};
protected:
    JumpStmt(LabelStmt* label):label_(label) {}
private:
    LabelStmt* label_;
    int label_tag;
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
class FuncDecl:public Stmt {
    friend class Generator;
public:
    FuncDecl(Identifier* ident,LabelStmt* label,CompoundStmt* body,std::vector<Object*>* params,bool global):
        ident_(ident),retLabel_(label),params_(params),global_(global){}
    void Accept(Visitor *v) override;
private:
    Identifier* ident_;
    LabelStmt* retLabel_;
    CompoundStmt* body_;
    ParamList * params_;
    bool global_;
};
class EmptyStmt:public Stmt{
public:
    void Accept(Visitor* v) override;
    virtual ~EmptyStmt();
protected:
    EmptyStmt(){}
};

class ReturnStmt:public Stmt{
    friend class Generator;
public:
    ~ReturnStmt(){};
    void Accept(Visitor* v) override;
protected:
    ReturnStmt(Expr* expr):expr_(expr){}
private:
    Expr* expr_;
};

/* Array, struct, union, enum and so on, but we have enumerator */
class CompoundStmt:public Stmt{
    friend class Generator;
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
    friend class Generator;
public:
    void Accept(Visitor* v) override;
    unsigned GetOp() { return op_; }
    bool IsLVal() override{

    }
    void TypeChecking() override{

    }
protected:
    BinaryOp(Expr* lhs, Expr* rhs,unsigned op):
        lhs_(lhs),rhs_(rhs),op_(op){

    }

private:
    Expr* lhs_;
    Expr* rhs_;
    unsigned op_;
};

/*
 * "++"
 * "&"
 * "+"
 * "-"
 * "~"
 * "!"
 */
class UnaryOp : public Expr{
    friend class Generator;
public:
    void Accept(Visitor* v) override;
    virtual bool IsVal();
    void TypeChecking() override{

    }
protected:
    int op_;
    Expr* operand_;
};

/* ? true_expr : false_expr ;  */
class ConditionalOp:public Expr{
    friend class Generator;
public:
    void Accept(Visitor* v) override;
    virtual bool IsLVal() {return false;}
    void TypeChecking() override;
protected:
    ConditionalOp(Expr* cond,Expr* true_expr,Expr* false_expr):
        cond_(cond),true_expr_(true_expr),false_expr_(false_expr){}
private:
    Expr* cond_;
    Expr* true_expr_;
    Expr* false_expr_;
};
class FuncCall:public Expr{
    friend class Generator;
public:
    using ArgList = std::vector<Expr*>;
public:
    void Accept(Visitor* v) override;
    virtual bool IsLVal(){return false;} ;
    void TypeChecking();
protected:
    FuncCall(Identifier* func,LabelStmt* label,std::vector<Expr*>* args):
        func_(func),retLabel_(label),args_(args){}
private:
    Identifier* func_;
    LabelStmt* retLabel_;
    ArgList* args_;
};
class TempVar:public Expr{
public:
    void Accept(Visitor* v) override;
    bool IsLVal(){return true;}
protected:
    TempVar(){

    }
private:
    int tag_;
};
class Constant:public Expr{
    friend class Generator;
public:
    virtual void Accept(Visitor* v) override;
    bool IsLVal() {return false;}
    virtual void TypeChecking() { }
protected:
    Constant(unsigned type, bool global):global_(global),type_(type){}
    Identifier *name;
    bool global_;
    unsigned type_; // integer,char,double and so on.
    union Value{
        int i;
        double d;
        float f;
        char c;
    };
};
// Ojbect,struct/enum/union,function,label.
class Identifier:public Expr{
    friend class Generator;
public:
    void Accept(Visitor* v) override;
    virtual bool IsLVal() { }
    virtual void TypeChecking() {}
protected:
    Identifier(std::string* name):name_(name){};
private:
    std::string* name_;
};
// Everything except FuncDecl
class Declaration:public Stmt{
    friend class Generator;
public:
    void Accept(Visitor* v) override;
    virtual bool IsLVal() {return false;}
    virtual void TypeChecking() {}
    void SetGlobal(){
        global_ = true;
    }
protected:
    Declaration(Identifier* name,Object* obj,bool global):
        name_(name),obj_(obj),global_(global){}
private:
    Identifier* name_;
    Object* obj_;
    bool global_;
    unsigned type_;
    // init values needed.
};

class Enumerator:public Identifier{
public:
    void Accept(Visitor* v) override;
protected:
    //Enumerator(Constant* cst):constant_(cst){}
    Constant* constant_;
};
class Object:public Identifier {
    friend class Generator;
public:
private:
    Declaration* decl_;
    bool global_;
};

#endif 