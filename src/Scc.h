#ifndef SCC_H
#define SCC_H

#include "Core.h"
#include "Scanner.h"
#include "Parser.h"
#include "Gen.h"

#include <string>

class Scc{
public:
    Scc(int argc,char** argv){
        astFile_ = "ast.html";
        objFile_ = "a.asm";
        irFile_ = "ir.txt";
        GetOpt(argc,argv); // initialize them in parse
    }
    void GetOpt(int argc,char** argv);
    void Exec();
private:
    std::string astFile_;
    std::string objFile_;
    std::string irFile_;
    std::string inputFile_;
private:
    Scanner* scanner_;
    Parser* parser_;
    Generator* gen_;

};

#endif