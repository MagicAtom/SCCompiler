#ifndef SCC_GEN_H
#define SCC_GEN_H

#include "Ast.h"
#include "Visitor.h"

class Parser;

class Generator:public Visitor{
public:
    void OutputFile();
    void Gen();
private:
    static Parser* parser_;
private:
    void EmitFunc(); // A function
    void EmitDecl(); // global variable
    void GenAddr();
    void GenExpr();
    void GenDeclInit();
    void GenData();
    // one-to-one with parser, add as needed.
    void GenAndOp();
    void GenDivOp();
};

#endif