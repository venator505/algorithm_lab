#pragma once

#include "token.h"

namespace ybt {
namespace structure {
namespace parser {

class CalculatorToken : public Token
{
public:
    enum Type
    {
        _EOF,
        DIGITS,
        FACTOROP,
        EXPROP,
        LBRACKET,
        RBRACKET
    };
    CalculatorToken(Type type, const std::string value) : Token(type, value) {}
};
} // namespace parser
} // namespace structure
} // namespace ybt