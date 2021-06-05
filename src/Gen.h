#ifndef SCC_GEN_H
#define SCC_GEN_H

static char *REGS[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
static char *SREGS[] = {"dil", "sil", "dl", "cl", "r8b", "r9b"};
static char *MREGS[] = {"edi", "esi", "edx", "ecx", "r8d", "r9d"};

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