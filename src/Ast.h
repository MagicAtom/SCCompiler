#ifndef SCC_AST_H
#define SCC_AST_H

#include "Token.h"
#include "Type.h"
#include <string>
#include <iostream>

// Forward Definition
class Generator;
class Visitor;

class ASTNode;
// Expressions
class Expression;
class ForExpr;
class WhileExpr;
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
class Parameter;
class Program;

using ParamList = std::vector<Parameter*>;
using IdentList = std::vector<Identifier*>;
using ASTList = std::vector<ASTNode*>;

typedef struct Initializer {
    Initializer(Type* type,Expression* expr):type_(type),expr_(expr){}
    Expression* expr_;
    Type* type_;
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
    llvm::BasicBlock* afterBB;
    int label = -1;
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
    IfStmt(Expression* cond,Stmt* then,Stmt* els):cond_(cond),then_(then),else_(els){}
private:
    Expression* cond_;
    Stmt* then_;
    Stmt* else_;
};

class Expression:public Stmt{
    friend class Generator;
public:
    Expression() {}
    Expression(Token* tok):token_(tok){ }
    void Accept(Visitor* v) override;
    const Token* Tok() const { return token_; }
    virtual ~Expression(){};
private:
    Token* token_;
    std::string name_;
};
class ForExpr : public Expression{
    friend class Generator;
public:
    void Accept(Visitor *v) override;
    ForExpr(Expression* start,Expression* end,Expression* value, Stmt* body,bool add):
        start_(start),end_(end),value_(value),body_(body),isAdd(add){}
private:
    bool isAdd;
    Expression* start_,*end_,*value_;
    Stmt* body_;
};
class WhileExpr: public Expression{
    friend class Generator;
public:
    void Accept(Visitor *v) override;
private:
    Expression *condition;
    Stmt *body;
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
    FuncDecl(Identifier* ident,CompoundStmt* body,std::vector<Parameter*>* params,Expression* retexpr, bool global):
        ident_(ident),retexpr_(retexpr),params_(params),global_(global){}
    void Accept(Visitor *v) override;
private:
    Identifier* ident_;
    Type* type_;
    CompoundStmt* body_;
    ParamList * params_;
    bool global_;
    Expression* retexpr_;
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
    ReturnStmt(Expression* expr):expr_(expr){}
private:
    Expression* expr_;
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
class BinaryOp:public Expression{
    friend class Generator;
public:
    void Accept(Visitor* v) override;
    unsigned GetOp() { return op_; }
protected:
    BinaryOp(Expression* lhs, Expression* rhs,unsigned op):
        lhs_(lhs),rhs_(rhs),op_(op){}

private:
    Expression* lhs_;
    Expression* rhs_;
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
class UnaryOp : public Expression{
    friend class Generator;
public:
    void Accept(Visitor* v) override;
protected:
    int op_;
    Expression* operand_;
};

/* ? true_expr : false_expr ;  */
class ConditionalOp:public Expression{
    friend class Generator;
public:
    void Accept(Visitor* v) override;
protected:
    ConditionalOp(Expression* cond,Expression* true_expr,Expression* false_expr):
        cond_(cond),true_expr_(true_expr),false_expr_(false_expr){}
private:
    Expression* cond_;
    Stmt* true_expr_;
    Stmt* false_expr_;
};
class FuncCall:public Expression{
    friend class Generator;
public:
    using ArgList = std::vector<Expression*>;
public:
    void Accept(Visitor* v) override;
protected:
    FuncCall(Identifier* func,LabelStmt* label,std::vector<Expression*>* args):
        func_(func),retLabel_(label),args_(args){}
private:
    Identifier* func_;
    LabelStmt* retLabel_;
    ArgList* args_;
};
class TempVar:public Expression{
public:
    void Accept(Visitor* v) override;
protected:
    TempVar(){

    }
private:
    int tag_;
};
class Constant:public Expression{
    friend class Generator;
public:
    virtual void Accept(Visitor* v) override;
    Constant* New(Token* tok, int tag, int val);
    Constant(Type* type, bool global):global_(global),type_(type){}
protected:
    Identifier *name;
    bool global_;
    Type* type_; // integer,char,double and so on.
    union Value{
        int i;
        double d;
        float f;
        char c;
    };
};
// Ojbect,struct/enum/union,function,label.
class Identifier:public Expression{
    friend class Generator;
public:
    void Accept(Visitor* v) override;
protected:
    Identifier(std::string* name):name_(name){};
private:
    std::string* name_;
};
class Declaration : public Expression {
    friend class Generator;
public:
    Declaration(IdentList* ident,Type* type):idents_(ident),type_(type) {}
    Declaration(IdentList* ident,Type* type,bool global):idents_(ident),type_(type),global_(global) {}
    Declaration(IdentList* ident,Type* type,bool global,bool isConst):
        idents_(ident),type_(type),global_(global),isConst_(isConst) {}
    void Accept(Visitor* v) override;
    void SetGlobal() { global_ = true;}
    void SetConst() {isConst_ = true;}
private:
    IdentList * idents_;
    Type* type_;
    bool global_;
    bool isStatic_; // Not support yet
    bool isConst_;
};
class Enumerator:public Stmt{
public:
    Enumerator(IdentList* idents):idents_(idents){}
    void Accept(Visitor* v) override;
protected:
    IdentList* idents_;
};
class Parameter : public Stmt {
    friend class Generator;
public:
    void Accept(Visitor* v) override;
protected:
    Parameter(IdentList *il,bool isVar):
        idents_(il),isVar_(isVar) {}
private:
    IdentList* idents_;
    bool isVar_;
    Type* type_;
};
class Program : public ASTNode {
    friend class Generator;
public:
    virtual void Accept(Visitor* v) override;
    void Add(ASTNode* ast) {astList.push_back(ast);}
private:
    ASTList astList;
};
#endif 