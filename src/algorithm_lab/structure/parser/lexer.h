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

    virtual Token* nextToken() = 0;

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
};
} // namespace parser
} // namespace structure
} // namespace ybt