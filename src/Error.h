#ifndef ERROR_H
#define ERROR_H

#include <memory>
#include "Ast.h"

std::unique_ptr<ASTNode> logError(const char* str){
    fprintf(stderr,"LogError:%s\n",str);
    return nullptr;
};

#endif