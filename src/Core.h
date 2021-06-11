/* 
 * This is for some io operations
 * or some helpers to load parameter
 * or some constants can store here
 */

#ifndef CORE_H
#define CORE_H

#include <vector>

std::string* ReadFile(const std::string& fileName){
    
}

typedef struct {
    void **body;
    int len;
    int nalloc;
} Vector;

typedef struct Type {
    int kind;
    int size;
    int align;
    bool usig; // true if unsigned
    bool isstatic;
    // pointer or array
    struct Type *ptr;
    // array length
    int len;
    // struct
    Dict *fields;
    int offset;
    bool is_struct; // true if struct, false if union
    // bitfield
    int bitoff;
    int bitsize;
    // function
    struct Type *rettype;
    Vector *params;
    bool hasva;
    bool oldstyle;
} Type;

typedef struct {
    char* file;
    unsigned line;
    unsigned column;
} SourceLoc;

typedef struct{
    int count; // token index
    int kind;
    int line;
    int column;
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
}Token;

#endif