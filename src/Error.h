#ifndef _ERROR_H_
#define _ERROR_H_


struct CodeLocation;
class Token;
class Expression;

void Error(const char* format, ...);
void Error(const CodeLocation& loc, const char* format, ...);
void Error(const Token* tok, const char* format, ...);
void Error(const Expression* expr, const char* format, ...);

#endif
