#ifndef SCANNER_H
#define SCANNER_H

#include <string>

class Scanner {
public:
    Scanner(){}

    Scanner(const char* file){

    }
    virtual ~Scanner(){

    }

private:
    const char* text_;
    
private:
    int Next(); // go next
    int Peek(); // return nxt without move
    bool Try(int c){
        if(Peek() == c) {
            Next();
            return true;
        }
        return false;
    }
};

#endif