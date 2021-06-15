#ifndef _WINDS_TOKEN_H
#define _WINDS_TOKEN_H
#include"Core.h"
#include<unordered_map>
#include<set>

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


  static Token* Create(int tag, const CodeLocation& loc, const string& str, bool ws=false);
  static Token* Create(int tag);

  Token& operator=(const Token& example){
    tag_ = example.tag_;
    ws_ = example.ws_;
    loc_ = example.loc_;
    str_ = example.str_;
    hs_ = example.hs_? new HideSet(*example.hs_) : nullptr;
    return *this;
  }
  virtual ~Token();

  const static unordered_map<string,int > kwTypeMap{
  { "auto", Token::AUTO },
  { "break", Token::BREAK },
  { "case", Token::CASE },
  { "char", Token::CHAR },
  { "const", Token::CONST },
  { "continue", Token::CONTINUE },
  { "default", Token::DEFAULT },
  { "do", Token::DO },
  { "double", Token::DOUBLE },
  { "else", Token::ELSE },
  { "enum", Token::ENUM },
  { "extern", Token::EXTERN },
  { "float", Token::FLOAT },
  { "for", Token::FOR },
  { "goto", Token::GOTO },
  { "if", Token::IF },
  { "inline", Token::INLINE },
  { "int", Token::INT },
  { "long", Token::LONG },
  { "signed", Token::SIGNED },
  { "unsigned", Token::UNSIGNED },
  { "register", Token::REGISTER },
  { "restrict", Token::RESTRICT },
  { "return", Token::RETURN },
  { "short", Token::SHORT },
  { "sizeof", Token::SIZEOF },
  { "static", Token::STATIC },
  { "struct", Token::STRUCT },
  { "switch", Token::SWITCH },
  { "typedef", Token::TYPEDEF },
  { "union", Token::UNION },
  { "void", Token::VOID },
  { "volatile", Token::VOLATILE },
  { "while", Token::WHILE },
  { "_Alignas", Token::ALIGNAS },
  { "_Alignof", Token::ALIGNOF },
  { "_Atomic", Token::ATOMIC },
  { "__attribute__", Token::ATTRIBUTE },
  { "_Bool", Token::BOOL },
  { "_Complex", Token::COMPLEX },
  { "_Generic", Token::GENERIC },
  { "_Imaginary", Token::IMAGINARY },
  { "_Noreturn", Token::NORETURN },
  { "_Static_assert", Token::STATIC_ASSERT },
  { "_Thread_local", Token::THREAD },
};

  const static unordered_map<int, const char*> Token::TagLexMap{
    {'(',"("},
    {')',")"},
    {'[',"["},
    {']',"]"},
    { ':', ":" },
    { ',', "," },
    { ';', ";" },
    { '+', "+" },
    { '-', "-" },
    { '*', "*" },
    { '/', "/" },
    { '|', "|" },
    { '&', "&" },
    { '<', "<" },
    { '>', ">" },
    { '=', "=" },
    { '.', "." },
    { '%', "%" },
    { '{', "{" },
    { '}', "}" },
    { '^', "^" },
    { '~', "~" },
    { '!', "!" },
    { '?', "?" },
    { '#', "#" },

    { Token::DSHARP, "##" },
    { Token::PTR, "->" },
    { Token::INC, "++" },
    { Token::DEC, "--" },
    { Token::LEFT, "<<" },
    { Token::RIGHT, ">>" },
    { Token::LE, "<=" },
    { Token::GE, ">=" },
    { Token::EQ, "==" },
    { Token::NE, "!=" },
    { Token::LOGICAL_AND, "&&" },
    { Token::LOGICAL_OR, "||" },
    { Token::MUL_ASSIGN, "*=" },
    { Token::DIV_ASSIGN, "/=" },
    { Token::MOD_ASSIGN, "%=" },
    { Token::ADD_ASSIGN, "+=" },
    { Token::SUB_ASSIGN, "-=" },
    { Token::LEFT_ASSIGN, "<<=" },
    { Token::RIGHT_ASSIGN, ">>=" },
    { Token::AND_ASSIGN, "&=" },
    { Token::XOR_ASSIGN, "^=" },
    { Token::OR_ASSIGN, "|=" },
    { Token::ELLIPSIS, "..." },

    { Token::AUTO, "auto" },
    { Token::BREAK, "break" },
    { Token::CASE, "case" },
    { Token::CHAR, "char" },
    { Token::CONST, "const" },
    { Token::CONTINUE, "continue" },
    { Token::DEFAULT, "default" },
    { Token::DO, "do" },
    { Token::DOUBLE, "double" },
    { Token::ELSE, "else" },
    { Token::ENUM, "enum" },
    { Token::EXTERN, "extern" },
    { Token::FLOAT, "float" },
    { Token::FOR, "for" },
    { Token::GOTO, "goto" },
    { Token::IF, "if" },
    { Token::INLINE, "inline" },
    { Token::INT, "int" },
    { Token::LONG, "long" },
    { Token::SIGNED, "signed" },
    { Token::UNSIGNED, "unsigned" },
    { Token::REGISTER, "register" },
    { Token::RESTRICT, "restrict" },
    { Token::RETURN, "return" },
    { Token::SHORT, "short" },
    { Token::SIZEOF, "sizeof" },
    { Token::STATIC, "static" },
    { Token::STRUCT, "struct" },
    { Token::SWITCH, "switch" },
    { Token::TYPEDEF, "typedef" },
    { Token::UNION, "union" },
    { Token::VOID, "void" },
    { Token::VOLATILE, "volatile" },
    { Token::WHILE, "while" },
    { Token::ALIGNAS, "_Alignas" },
    { Token::ALIGNOF, "_Alignof" },
    { Token::ATOMIC, "_Atomic" },
    { Token::ATTRIBUTE, "__attribute__" },
    { Token::BOOL, "_Bool" },
    { Token::COMPLEX, "_Complex" },
    { Token::GENERIC, "_Generic" },
    { Token::IMAGINARY, "_Imaginary" },
    { Token::NORETURN, "_Noreturn" },
    { Token::STATIC_ASSERT, "_Static_assert" },
    { Token::THREAD, "_Thread_local" },

    { Token::END, "(eof)" },
    { Token::IDENTIFIER, "(identifier)" },
    { Token::CONSTANT, "(constant)" },
    { Token::LITERAL, "(string literal)" },
  };

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
  }

  void FinalizeSubset(bool leadingws, const HideSet& hs){

  }

  


private :
  TokenList* tokenlist_;
  mutable TokenList::iterator head_;
  TokenList::iterator end_;
  Parser* parser_{nullptr};
  int exceed_end {0};

};

#endif