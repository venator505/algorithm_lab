#pragma once

#include <stdexcept>
#include <string>
#include "lexer.h"
#include "calculator_token.h"
#include "token.h"

namespace ybt {
namespace structure {
namespace parser {
class CalculatorLexer : public Lexer
{
public:
    CalculatorLexer(const std::string& input) : Lexer(input) {}

    Token nextToken() override
    {
        while (c != EOF)
        {
            switch (c)
            {
                case '(':
                    consume();
                    return CalculatorToken(CalculatorToken::Type::LBRACKET,
                                           "(");
                case ')':
                    consume();
                    return CalculatorToken(CalculatorToken::Type::RBRACKET,
                                           ")");
                case '+':
                case '-': return op(CalculatorToken::Type::EXPROP);
                case '^':
                case '*':
                case '/': return op(CalculatorToken::Type::FACTOROP);
                case ' ': consume(); continue;
                default:
                    if (isdigit(c)) return digits();
                    throw std::runtime_error("invaild charactor");
            }
        }
        return CalculatorToken(CalculatorToken::Type::_EOF, "EOF");
    }

private:
    Token digits()
    {
        std::string value;
        _digits(value);
        if (c == '.')
        {
            value += c;
            consume();
            _digits(value);
        }
        return CalculatorToken(CalculatorToken::Type::DIGITS, value);
    }

    Token op(CalculatorToken::Type type)
    {
        std::string value;
        value += c;
        consume();
        return CalculatorToken(type, value);
    }
};
} // namespace parser
} // namespace structure
} // namespace ybt