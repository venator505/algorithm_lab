#pragma once

#include <cstdio>
#include "lexer.h"
#include "token.h"

namespace ybt {
namespace structure {
namespace parser {

enum HTMLToken
{
    TAG_L,
    TAG_R,
    TAG_SLASH,
    DIGITS,
    NAME,
    ASSIGN,
    SQUOTE,
    SQVALUE,
    DQUOTE,
    DQVALUE
};

class HtmlLexer : public Lexer
{
public:
    HtmlLexer(const std::string& input) : Lexer(input) {}

    Token nextToken() override
    {
        while (c != EOF)
        {
            switch (c)
            {
                case '<': consume(); return Token(HTMLToken::TAG_L, "<");
                case '>': consume(); return Token(HTMLToken::TAG_R, ">");
                case '/': consume(); return Token(HTMLToken::TAG_SLASH, "/");
                case '=': consume(); return Token(HTMLToken::ASSIGN, "=");
                case '\'': consume(); return Token(HTMLToken::SQUOTE, "\'");
                case '\"': consume(); return Token(HTMLToken::DQUOTE, "\"");
                case ' ':
                case '\t':
                case '\n': ws(); continue;
                default:
                    if (isalpha(c)) return Token(HTMLToken::NAME, name());
            }
        }
        return Token(EOF, "");
    }

private:
    void ws() { consume(); }

    std::string name()
    {
        std::string value;
        while (isalpha(c) or isdigit(c))
        {
            value += c;
            consume();
        }
        return value;
    }
};
} // namespace parser
} // namespace structure
} // namespace ybt