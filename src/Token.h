#ifndef _WINDS_TOKEN_H
#define _WINDS_TOKEN_H
#include"Core.h"
#include"Parser.h"
#include<stdio.h>
#include<unordered_map>
#include<set>
#include<list>
#include<cassert>
#include<iostream>
#include<cstring>

using namespace std;
struct CodeLocation{
  const string* filename;
  const char* frag_begin;
  unsigned linenum;
  unsigned column;

  const char* Tail() const{
    return frag_begin + column - 1;
  }

};

using HideSet = std::set<std::string>;
using TokenList = list<const Token*>;

class Token{
    friend class Scanner;
public:
 enum {
    // Punctuators
    LPAR = '(',
    RPAR = ')',
    LSQB = '[',
    RSQB = ']',
    COLON = ':',
    COMMA = ',',
    SEMI = ';',
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    OR = '|',
    AND = '&',
    XOR = '^',
    LESS = '<',
    GREATER = '>',
    EQUAL = '=',
    DOT = '.',
    MOD = '%',
    LBRACE = '{',
    RBRACE = '}',
    TILDE = '~',
    NOT = '!',
    COND = '?',
    SHARP = '#',
    NEW_LINE = '\n',

    DSHARP = 128, // '##'
    PTR,
    INC,
    DEC,
    LEFT,
    RIGHT,
    LE,
    GE,
    EQ,
    NE,
    LOGICAL_AND,
    LOGICAL_OR,

    MUL_ASSIGN,
    DIV_ASSIGN,
    MOD_ASSIGN,
    ADD_ASSIGN,
    SUB_ASSIGN,
    LEFT_ASSIGN,
    RIGHT_ASSIGN,
    AND_ASSIGN,
    XOR_ASSIGN,
    OR_ASSIGN,

    ELLIPSIS,
    // Punctuators end

    // KEYWORD BEGIN
    // TYPE QUALIFIER BEGIN
    CONST,
    RESTRICT,
    VOLATILE,
    ATOMIC,
    // TYPE QUALIFIER END

    // TYPE SPECIFIER BEGIN
    VOID,
    CHAR,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    SIGNED,
    UNSIGNED,
    BOOL,		// _Bool
    COMPLEX,	// _Complex
    STRUCT,
    UNION,
    ENUM,
    // TYPE SPECIFIER END

    ATTRIBUTE, // GNU extension __attribute__
    // FUNCTION SPECIFIER BEGIN
    INLINE,
    NORETURN,	// _Noreturn
    // FUNCTION SPECIFIER END

    ALIGNAS, // _Alignas
    // For syntactic convenience
    STATIC_ASSERT, // _Static_assert
    // STORAGE CLASS SPECIFIER BEGIN
    TYPEDEF,
    EXTERN,
    STATIC,
    THREAD,	// _Thread_local
    AUTO,
    REGISTER,
    // STORAGE CLASS SPECIFIER END
    BREAK,
    CASE,
    CONTINUE,
    DEFAULT,
    DO,
    ELSE,
    FOR,
    GOTO,
    IF,
    RETURN,
    SIZEOF,
    SWITCH,
    WHILE,
    ALIGNOF, // _Alignof
    GENERIC, // _Generic
    IMAGINARY, // _Imaginary
    // KEYWORD END

    IDENTIFIER,
    CONSTANT,
    I_CONSTANT,
    C_CONSTANT,
    F_CONSTANT,
    LITERAL,

    // For the parser, a identifier is a typedef name or user defined type
    POSTFIX_INC,
    POSTFIX_DEC,
    PREFIX_INC,
    PREFIX_DEC,
    ADDR,  // '&'
    DEREF, // '*'
    PLUS,
    MINUS,
    CAST,

    // For preprocessor
    PP_IF,
    PP_IFDEF,
    PP_IFNDEF,
    PP_ELIF,
    PP_ELSE,
    PP_ENDIF,
    PP_INCLUDE,
    PP_DEFINE,
    PP_UNDEF,
    PP_LINE,
    PP_ERROR,
    PP_PRAGMA,
    PP_NONE,
    PP_EMPTY,


    IGNORE,
    INVALID,
    END,
    NOTOK = -1,
  };
  int tag_;
  string str_;
  bool ws_;
  CodeLocation loc_;
  HideSet* hs_ { nullptr };


  static Token* New(int tag, const CodeLocation& loc, const string& str, bool ws=false);
  static Token* New(int tag);
  static Token* New(const Token& example);

  Token& operator=(const Token& example){
    tag_ = example.tag_;
    ws_ = example.ws_;
    loc_ = example.loc_;
    str_ = example.str_;
    hs_ = example.hs_? new HideSet(*example.hs_) : nullptr;
    return *this;
  }
  virtual ~Token();

  const static unordered_map<string,int > kwTypeMap;

  const static unordered_map<int, const char*> Token::TagLexMap;

  static int KeyWordTag(const string& key) {
    auto kw = kwTypeMap.find(key);
    if(kwTypeMap.end() == kw)
      return Token::NOTOK;
    return kw->second;
  }

  static bool IsKeyWord(const string& name);
  static bool IsKeyWord(int tag){
    return CONST <= tag && tag<IDENTIFIER;
  }
  bool IsKeyWord() const{
    return IsKeyWord(tag_);
  }
  bool IsPuncuator() const{
    return 0 <= tag_ && tag_ <= ELLIPSIS;
  }
  bool IsLiteral() const{
    return tag_ == LITERAL;
  }
  bool IsConstant() const{
    return CONSTANT <= tag_ && tag_ <= F_CONSTANT;
  }
  bool IsIdentifier() const{
    return IDENTIFIER == tag_;
  }
  bool IsEOF() const{
    return tag_== END;
  }
  bool IsTypeSpecQual() const{
    return CONST <= tag_ && tag_ <= ENUM;
  }  
  bool IsDecl() const{
    return CONST <= tag_ && tag_ <= REGISTER;
  }
  static const char* MyLex(int tag){
    auto iter = TagLexMap.find(tag);
    if(iter == TagLexMap.end())
      return nullptr;
    
    return iter->second;
  }

private:
  explicit Token(int tag): tag_(tag){}
  Token(int tag, const CodeLocation& loc, const string&str, bool ws=false)
  : tag_(tag),ws_(ws),loc_(loc),str_(str){}

  Token(const Token& example){
    *this = example;
  }
  
};



class TokenSequence{
  friend class Preprocessor;

public :
  explicit TokenSequence(Token* tok){
    TokenSequence();
    InsertBack(tok);
  }
  explicit TokenSequence(TokenList* toklist)
    : tokenlist_(toklist),
      head_(toklist->begin()),
      end_(toklist->end()){}
  TokenSequence():  tokenlist_(new TokenList()),
                    head_(tokenlist_->begin()),
                    end_(tokenlist_->end()) {}
                  
  TokenSequence(TokenList* toklist,TokenList::iterator head,TokenList::iterator end):
                tokenlist_(toklist),head_(head),end_(end) {}
  const TokenSequence& operator=(const TokenSequence& example){
    tokenlist_ = example.tokenlist_;
    head_ = example.head_;
    end_ = example.end_;
    return *this;
  }

  void UpdateHeadLocation(const CodeLocation& loc){
    assert(!Empty());
    auto tok = const_cast<Token*>(Peek());
    tok->loc_ = loc;
  }

  void FinalizeSubset(bool leadingws, const HideSet& hs){
    auto ts = *this;
    while(!ts.Empty()){
      auto tok = const_cast<Token*>(ts.Next());
      if(!tok->hs_){
        tok->hs_ = new HideSet(hs);
      }
      else 
        tok->hs_->insert(hs.begin(),hs.end());
    }
    //when the token sequence is empty
    const_cast<Token*>(Peek())->ws_ = leadingws;
  }

  void Copy(const TokenSequence& example){
    tokenlist_ = new TokenList(example.head_,example.end_);
    head_ = tokenlist_->begin();
    end_ = tokenlist_->end();
    for (auto iter = head_; iter != end_;iter++){
      *iter = Token::New(**iter);
    }
  }

  const Token* Expect(int expect);
  bool Try(int tag){
    if(Peek()->tag_ == tag){
      Next();
      return true;
    }
    return false;
  }

  bool Test(int tag){
    return Peek()->tag_ == tag;
  }

  const Token*Next(){
    auto ret = Peek();
    if(!ret->IsEOF()){
      ++head_;
      Peek();   //error: skip newline token???
    }else{
      ++exceed_end;
    }
    return ret;
  }
  const Token* Peek() const;
  const Token* Peek2() {
    if(Empty())
    //return TOken::END
      return Peek();  
    Next();
    auto ret = Peek();
    PutBack();
    return ret;
  }

  void PutBack(){
    assert(head_ != tokenlist_->begin());
    if(exceed_end > 0){
      --exceed_end;
    }else{
      --head_;
      if((*head_)->tag_ == Token::NEW_LINE)
      PutBack();
    }
  }

  const Token* Back() const{
    auto back = end_;
    return *--back;
  }

  void PopBack(){
    assert(!Empty());
    assert(end_ == tokenlist_->end());
    auto size_eq = tokenlist_->back()==*head_;
    tokenlist_->pop_back();
    end_ = tokenlist_->end();
    if(size_eq)
      head_=end_;
  }

  TokenList::iterator Mark(){
    return head_;
  }
  void ResetTo(TokenList::iterator mark){
    head_ = mark;
  }
  bool Empty() const{
    return Peek()->tag_ == Token::END;
  }
  void InsertBack(TokenSequence& ts){
    //insert all Tokenlist of ts into this example
    tokenlist_->splice(end_,*ts.tokenlist_);
    //update headpointer and endpointer
    head_=tokenlist_->begin();
    end_=tokenlist_->end();
  }
  void InsertBack(const Token* tok){
    auto pos = tokenlist_->insert(end_,tok);
    //update headpointer and endpointer
    head_=tokenlist_->begin();
    end_=tokenlist_->end();
  }

  //preceding newline code
  void InsertFront(TokenSequence& ts){
    auto pos = GetInsertFrontPos();
    tokenlist_->splice(pos,*ts.tokenlist_);
    head_=tokenlist_->begin();
  }

  void InsertFront(const Token* tok){
    auto pos = GetInsertFrontPos();
    head_=tokenlist_->insert(pos,tok);
  }
  bool IsBeginOfLine() const;
  TokenSequence GetLine();
  void SetParser(Parser* parser){
    parser_ = parser;
  }

  void Print(FILE* fp=stdout) const;


  

private :
  TokenList::iterator GetInsertFrontPos(){
    auto pos = head_;
    if (pos == tokenlist_->begin())
      return pos;
    --pos;
    while(pos != tokenlist_->begin() && (*pos)->tag_ == Token::NEW_LINE)
      --pos;
    return ++pos;
  }

  TokenList* tokenlist_;
  TokenList::iterator head_ ;
  TokenList::iterator end_ ;
  Parser* parser_{nullptr};
  int exceed_end {0};

};

#endif