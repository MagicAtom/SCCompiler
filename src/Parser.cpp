#include "Parser.h"

void Parser::Parse()
{
    DefineBuiltins();
    Translate();
}