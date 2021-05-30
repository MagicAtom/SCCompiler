/*
 * Tokenizer
 * Scan and decompose the source code into preprocessing tokens.
 */

#ifndef SCANNER_H
#define SCANNER_H

#include "Core.h"
#include <string>
#include <vector>

struct Block{
    int line;
    int column;
    TokenList& tl;
};

using TokenList = std::vector<Token>;
using TokenSequence = std::vector<Block>;

class Scanner {
public:
    Scanner(){
        text_ = nullptr;
    }
    Scanner(const std::string& fileName):filename_(fileName){

    }
    virtual ~Scanner(){

    }
    void Scan(); // Core func
    void ReadFunc();
    void ReadDecl(Block& block,bool isGlobal);
    const TokenSequence& GetTS(){
        return ts_;
    }
    Token* ReadToken();
private:
    void SkipSpace(); // useless space
    void SkipComments(); // comments useless
    int Next(); // Go next
    int Peek(); // return nxt without move
    bool Try(int c){
        if(Peek() == c) {
            Next();
            return true;
        }
        return false;
    }
    void Back();
    bool IsFunc();
    Node* ReadFuncBody();
    /*
     * These functions can be implemented in Read Token
     * You can also add more here
     */
    Token* ReadNumber();
    Token* ReadString();
    /* 
     * Make token, you can make a stmt, decl as token and so on.
     * This is the part of tokenizer. And so on
     */
    Token* make_char();
    Token* make_integer();
private:
    std::string filename_;
    std::string* text_;
    TokenSequence ts_;
};

#endif