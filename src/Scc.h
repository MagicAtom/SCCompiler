#ifndef SCC_H
#define SCC_H

#include "Core.h"
#include "Scanner.h"
#include "Parser.h"
#include "Gen.h"

class Scc{
public:
    void GetOpt(int argc,char** argv);
    void Exec();
private:
    Scanner scanner_;
    Parser parser_;
    Generator gen_;
};

#endif