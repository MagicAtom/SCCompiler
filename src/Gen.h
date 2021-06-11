#ifndef SCC_GEN_H
#define SCC_GEN_H

class Generator{
public:
    void OutputFile();
    void Gen();
    void EmitFunc(); // A function
    void EmitDecl(); // global variable
private:
    void GenAddr();
    void GenExpr();
    void GenDeclInit();
    void GenData();
    // one-to-one with parser, add as needed.
    void GenAndOp();
    void GenDivOp();
    
};

#endif