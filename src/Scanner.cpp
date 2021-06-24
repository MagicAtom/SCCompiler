#include "Scanner.h"

    Token* Scanner::Scan() {
        if (Peek=='\n') {
            Next();
        }
        auto c = Next();
        switch (c) {
        case '#': return MakeToken(Try('#') ? Token::DSHARP: c);
        case ':': return MakeToken(Try('>') ? ']': c);
        case '(': case ')': case '[': case ']':
        case '?': case ',': case '{': case '}':
        case '~': case ';':
            return MakeToken(c);
        case '-':
            if (Try('>')) return MakeToken(Token::PTR);
            if (Try('-')) return MakeToken(Token::DEC);
            if (Try('=')) return MakeToken(Token::SUB_ASSIGN);
            return MakeToken(c);
        case '+':
            if (Try('+')) return MakeToken(Token::INC);
            if (Try('=')) return MakeToken(Token::ADD_ASSIGN);
            return MakeToken(c);
        case '<':
            if (Try('<')) return MakeToken(Try('=') ? Token::LEFT_ASSIGN: Token::LEFT);
            if (Try('=')) return MakeToken(Token::LE);
            if (Try(':')) return MakeToken('[');
            if (Try('%')) return MakeToken('{');
            return MakeToken(c);
        case '%':
            if (Try('=')) return MakeToken(Token::MOD_ASSIGN);
            if (Try('>')) return MakeToken('}');
            if (Try(':')) {
            if (Try('%')) {
                if (Try(':')) return MakeToken(Token::DSHARP);
                Back();
            }
            return MakeToken('#');
            }
            return MakeToken(c);
        case '>':
            if (Try('>')) return MakeToken(Try('=') ? Token::RIGHT_ASSIGN: Token::RIGHT);
            if (Try('=')) return MakeToken(Token::GE);
            return MakeToken(c);
        case '=': return MakeToken(Try('=') ? Token::EQ: c);
        case '!': return MakeToken(Try('=') ? Token::NE: c);
        case '&':
            if (Try('&')) return MakeToken(Token::LOGICAL_AND);
            if (Try('=')) return MakeToken(Token::AND_ASSIGN);
            return MakeToken(c);
        case '|':
            if (Try('|')) return MakeToken(Token::LOGICAL_OR);
            if (Try('=')) return MakeToken(Token::OR_ASSIGN);
            return MakeToken(c);
        case '*': return MakeToken(Try('=') ? Token::MUL_ASSIGN: c);
        case '/':
            if (Peek()=='/' || Peek() == '*') {
            SkipComments();
            return Scan();
            }
            return MakeToken(Try('=') ? Token::DIV_ASSIGN: c);
        case '^': return MakeToken(Try('=') ? Token::XOR_ASSIGN: c);
        case '.':
            if (Try('.')) {
            if (Try('.')) return MakeToken(Token::ELLIPSIS);
            Back();
            return MakeToken('.');
            }
            return MakeToken(c);
        case 'a' ... 't': case 'v' ... 'z': case 'A' ... 'K':
        case 'M' ... 'T': case 'V' ... 'Z': case '_': case '$':
        case '\\':
            // Universal character name is allowed in identifier
            if (Peek()== 'u' || Peek() == 'U')
            return MakeToken(Token::INVALID);
        case '\0': return MakeToken(Token::END);
        default: return MakeToken(Token::INVALID);
        }
    }
    Token* Scanner::ReadToken(){
        while (true) {
        auto tok = Scan();
        if (tok->tag_ == Token::END) {
        if (ts_.empty() || (ts_.back()->tag_ != Token::NEW_LINE)) {
            auto t = Token::New(*tok);
            t->tag_ = Token::NEW_LINE;
            t->str_ = "\n";
            ts.InsertBack(t);
        }
        break;
        } else {
        if (!ts_.empty() && ts_.back()->tag_ == Token::NEW_LINE)
            tok->ws_ = true;
        ts.InsertBack(tok);
        }
    }
    }
    void Scanner::SkipSpace(){
        while (isspace(Peek()) && Peek() != '\n') {
        token->ws_ = true;
        Next();
        }
    }
    void Scanner::SkipComments(){
        if (Try('/')) {
            
            while (!*c == 0) {
            if (Peek() == '\n')
                return;
            Next();
            }
            return;
        } else if (Try('*')) {
            while (!*c == 0) {
            auto c = Next();
            if (c  == '*' && Peek() == '/') {
                Next();
                return;
            }
            }
            Error(loc, "unterminated block comment");
        }
        assert(false);
    }
    int Scanner::Next(){
        int cur = Peek();
        ++c;
        if (cur == '\n') {
            ++loc.linenum;
            loc.column = 1;
            loc.frag_begin = c;
        } else {
            ++loc.column;
        }
        return cur;
    }
    int Scanner::Peek(){
        int cur = (uint8_t)(*c);
        if (cur == '\\' && c[1] == '\n') {
            c += 2;
            ++loc.linenum;
            loc.column = 1;
            loc.frag_begin = c;
            return Peek();
        }
        return cur;
    }

    void Scanner::Back(){
        int cur = *--c;
        if (cur == '\n' && c[-1] == '\\') {
            --loc.linenum;
            --c;
            return Back();
        } else if (cur == '\n') {
            --loc.linenum;
        } else {
            --loc.column;
        }
    }

    Token* Scanner::MakeToken(int tag) {
        token->tag_ = tag;
        auto& str = token->str_;
        str.resize(0);
        const char* p = token->loc_.frag_begin + token->loc_.column - 1;
        for (; p < p_; ++p) {
            if (p[0] == '\n' && p[-1] == '\\')
            str.pop_back();
            else
            str.push_back(p[0]);
        }
        return Token::New(token);
}