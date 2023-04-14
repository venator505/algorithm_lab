#pragma once

#include <cstdio>
#include <stdexcept>
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
                case '\'': return Token(HTMLToken::SQVALUE, quote_value('\''));
                case '\"': return Token(HTMLToken::DQVALUE, quote_value('\"'));
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

    std::string quote_value(char stop)
    {
        std::string value;
        consume();
        while (c != stop)
        {
            if (c == EOF)
            {
                throw std::runtime_error("unclosed quate");
            }
            value += c;
            consume();
        }
        consume();
        return value;
    }
};
} // namespace parser
} // namespace structure
} // namespace ybt