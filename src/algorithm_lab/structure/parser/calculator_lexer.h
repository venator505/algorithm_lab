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

    Token* nextToken() override
    {
        while (c != EOF)
        {
            switch (c)
            {
                case '(':
                    consume();
                    return new CalculatorToken(CalculatorToken::Type::LBRACKET,
                                               "(");
                case ')':
                    consume();
                    return new CalculatorToken(CalculatorToken::Type::RBRACKET,
                                               ")");
                case '+':
                case '-': return op(CalculatorToken::Type::EXPROP);
                case '*':
                case '/': return op(CalculatorToken::Type::FACTOROP);
                case ' ': consume(); continue;
                default:
                    if (isdigit(c)) return digits();
                    throw std::runtime_error("vaild charactor");
            }
        }
        return new CalculatorToken(CalculatorToken::Type::_EOF, "EOF");
    }

    Token* digits()
    {
        int num = 0;
        while (isdigit(c))
        {
            num *= 10;
            num += c - '0';
            consume();
        }
        std::string value = std::to_string(num);
        return new CalculatorToken(CalculatorToken::Type::DIGITS, value);
    }

    Token* op(CalculatorToken::Type type)
    {
        std::string value;
        value += c;
        consume();
        return new CalculatorToken(type, value);
    }

private:
    bool isdigit(char c) { return c >= '0' && c <= '9'; }
};
} // namespace parser
} // namespace structure
} // namespace ybt