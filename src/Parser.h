#ifndef PARSER_H
#define PARSER_H

#include "Ast.h"
#include "Token.h"

// Parser gen Ast
class Parser {
public:
    Parser(){

    }
    ~Parser() {}

    void Parse(); // this is main function
    void Translate();
    void DefineBuiltins();

private:
    
};

#endif