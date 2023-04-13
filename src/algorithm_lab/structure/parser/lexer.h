#pragma once

#include <cstdio>
#include "token.h"
namespace ybt {
namespace structure {
namespace parser {
class Lexer
{
public:
    Lexer(const std::string& input) : input(input), c(input[0]), p(0) {}

    size_t size() const { return input.size(); }

    virtual Token nextToken() = 0;

    // virtual void match(char c) = 0;

    void consume()
    {
        ++p;
        if (p >= input.size())
            c = EOF;
        else
            c = input[p];
    }

protected:
    const std::string input;
    char c;
    size_t p;

    void ws()
    {
        while (c == ' ' or c == '\n' or c == '\t') consume();
    }

    void _digits(std::string& value)
    {
        while (isdigit(c))
        {
            value += c;
            consume();
        }
    }

    bool isalpha(char c)
    {
        return (c >= 'A' && c <= 'Z') or (c >= 'a' && c <= 'z');
    }
    bool isdigit(char c) { return c >= '0' && c <= '9'; }
};
} // namespace parser
} // namespace structure
} // namespace ybt