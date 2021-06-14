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
    hs_ = example.hs_? new HideSet(*other.hs_) : nullptr;
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

const unordered_map<int, const char*> 

  static int KeyWordTag(const string& key) {
    auto kw = kwTypeMap.find(key);

  }

  
};





#endif