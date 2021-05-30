#ifndef SCC_GEN_H
#define SCC_GEN_H

class Generator{
public:
    void OutputFile();
    void Gen();
private:
    // one-to-one with parser, add as needed.
    void GenAndOp();
    void GenDivOp();
};

#endif