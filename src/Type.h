//
// Created by 宋庭聿 on 2021/6/16.
//

#ifndef SCC_TYPE_H
#define SCC_TYPE_H


enum SCCType{
    _INT,
    _CHAR,
    _BOOL,
    _FLOAT,
    _DOUBLE,
    _VOID,
    _ARRAY,
    _STRUCT,
    _USER_DEFINED,

};

class Type {
public:
    Type(unsigned type):type_(type){
        var_ = false;
        global_ = false;
        length_ = 0;
    }
    Type(unsigned  type,int global):type_(type),global_(global){
        var_ = false;
        length_ = 0;
    }
    // This is For
    Type(unsigned type, bool var, bool global,unsigned length):type_(type),var_(var),global_(global),length_(length){
        assert(type == SCCType::_ARRAY);
    }
    unsigned type_;
    bool var_;
    bool global_;
    unsigned length_;
};


#endif //SCC_TYPE_H
