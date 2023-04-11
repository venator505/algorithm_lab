#include <cstddef>
#include <iostream>
#include "algorithm_lab/structure/parser/calculator_lexer.h"
#include "algorithm_lab/structure/parser/calculator_token.h"
#include "algorithm_lab/structure/parser/token.h"
#include "gtest/gtest.h"

using namespace ybt::structure::parser;

TEST(Caculator, Lexer)
{
    CalculatorLexer lexer("16 * (5 + 2) - 4 / 2");
    std::vector<CalculatorToken> expect{
        CalculatorToken(CalculatorToken::Type::DIGITS, "16"),
        CalculatorToken(CalculatorToken::Type::FACTOROP, "*"),
        CalculatorToken(CalculatorToken::Type::LBRACKET, "("),
        CalculatorToken(CalculatorToken::Type::DIGITS, "5"),
        CalculatorToken(CalculatorToken::Type::EXPROP, "+"),
        CalculatorToken(CalculatorToken::Type::DIGITS, "2"),
        CalculatorToken(CalculatorToken::Type::RBRACKET, ")"),
        CalculatorToken(CalculatorToken::Type::EXPROP, "-"),
        CalculatorToken(CalculatorToken::Type::DIGITS, "4"),
        CalculatorToken(CalculatorToken::Type::FACTOROP, "/"),
        CalculatorToken(CalculatorToken::Type::DIGITS, "2")};
    auto t = lexer.nextToken();
    for (size_t i = 0;
         i < expect.size() && t.get_type() != CalculatorToken::Type::_EOF;
         ++i, t = lexer.nextToken())
    {
        ASSERT_EQ(t, expect[i]);
    }
    ASSERT_EQ(t.get_type(), CalculatorToken::Type::_EOF);
}