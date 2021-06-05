#ifndef SCC_H
#define SCC_H

#include "Core.h"
#include "Scanner.h"
#include "Parser.h"
#include "Gen.h"

class Scc{
public:
    Scc(int argc,char** argv){
        GetOpt(argc,argv); // initialize them in parse
    }
    void GetOpt(int argc,char** argv);
    void SetUp();
    void Exec();
private:
    char* openfile_;
    char* genfile_;
private:
    Scanner scanner_;
    Parser parser_;
    Generator gen_;
};

#endif