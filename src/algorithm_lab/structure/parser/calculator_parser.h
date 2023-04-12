#pragma once
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include "calculator_token.h"
#include "parser.h"
namespace ybt {
namespace structure {
namespace parser {

/*
expr : term (OP1 term)*
term : factor (OP2 FACTOR)*
factor : digits | expr | '('factor')' | '-'factor
*/
class CalculatorParser : public Parser
{
public:
    CalculatorParser(Lexer* input) : Parser(input, 1) {}
    double expr()
    {
        double value = term();
        if (LT(0) == CalculatorToken::EXPROP)
        {
            while (LT(0) == CalculatorToken::EXPROP)
            {
                evalue(value, std::bind(&CalculatorParser::term, this));
            }
        }
        return value;
    }

private:
    double term()
    {
        double value = factor();
        while (LT(0) == CalculatorToken::Type::FACTOROP)
        {
            evalue(value, std::bind(&CalculatorParser::factor, this));
        }
        return value;
    }

    double factor()
    {
        if (LT(0) == CalculatorToken::Type::DIGITS)
        {
            double value = std::atof(LV(0).c_str());
            match(CalculatorToken::Type::DIGITS);
            return value;
        }
        else if (LT(0) == CalculatorToken::Type::LBRACKET)
        {
            match(CalculatorToken::Type::LBRACKET);
            double value = expr();
            match(CalculatorToken::Type::RBRACKET);
            return value;
        }
        else if (LT(0) != CalculatorToken::Type::_EOF)
        {
            if (LV(0) == "-")
            {
                consume();
                return -factor();
            }
            return expr();
        }
        else
            throw std::runtime_error("ErrorFactor");
    }

    using f = std::function<double()>;
    void evalue(double& value, f func)
    {
        auto op = LV(0);
        consume();
        if (op == "+")
            value += func();
        else if (op == "-")
            value -= func();
        else if (op == "*")
            value *= func();
        else if (op == "/")
            value /= func();
        else if (op == "^")
            value = std::pow(value, func());
        else
            throw std::runtime_error("unsupported operator");
    }
};
} // namespace parser
} // namespace structure
} // namespace ybt