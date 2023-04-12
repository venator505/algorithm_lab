#include <cstddef>
#include <exception>
#include <iostream>
#include "algorithm_lab/structure/parser/calculator_lexer.h"
#include "algorithm_lab/structure/parser/calculator_token.h"
#include "algorithm_lab/structure/parser/token.h"
#include "algorithm_lab/structure/parser/calculator_parser.h"
#include "gtest/gtest.h"

using namespace ybt::structure::parser;

TEST(Caculator, Lexer)
{
    CalculatorLexer lexer("16 * (5 + 2.4) - 4 / 2.6");
    std::vector<CalculatorToken> expect{
        CalculatorToken(CalculatorToken::Type::DIGITS, "16"),
        CalculatorToken(CalculatorToken::Type::FACTOROP, "*"),
        CalculatorToken(CalculatorToken::Type::LBRACKET, "("),
        CalculatorToken(CalculatorToken::Type::DIGITS, "5"),
        CalculatorToken(CalculatorToken::Type::EXPROP, "+"),
        CalculatorToken(CalculatorToken::Type::DIGITS, "2.4"),
        CalculatorToken(CalculatorToken::Type::RBRACKET, ")"),
        CalculatorToken(CalculatorToken::Type::EXPROP, "-"),
        CalculatorToken(CalculatorToken::Type::DIGITS, "4"),
        CalculatorToken(CalculatorToken::Type::FACTOROP, "/"),
        CalculatorToken(CalculatorToken::Type::DIGITS, "2.6")};
    auto t = lexer.nextToken();
    for (size_t i = 0;
         i < expect.size() && t.get_type() != CalculatorToken::Type::_EOF;
         ++i, t = lexer.nextToken())
    {
        ASSERT_EQ(t, expect[i]);
    }
    ASSERT_EQ(t.get_type(), CalculatorToken::Type::_EOF);
}

void ASSERT_EXPR_CORRECT(const std::string& expr, double expect)
{
    CalculatorLexer lexer(expr);
    CalculatorParser parser(&lexer);
    double actural = parser.expr();
    ASSERT_FLOAT_EQ(actural, expect);
}

TEST(Caculator, Parser)
{
    ASSERT_EXPR_CORRECT("1", 1);
    ASSERT_EXPR_CORRECT("-1", -1);
    ASSERT_EXPR_CORRECT("3.14", 3.14);
    ASSERT_EXPR_CORRECT("-3.14", -3.14);
    ASSERT_EXPR_CORRECT("1 + 2", 3);
    ASSERT_EXPR_CORRECT("1 - 2", -1);
    ASSERT_EXPR_CORRECT("2 * 3", 6);
    ASSERT_EXPR_CORRECT("4 / 2", 2);
    ASSERT_EXPR_CORRECT("4.2 + 3.8", 8);
    ASSERT_EXPR_CORRECT("4.2 - 3.8", 0.4);
    ASSERT_EXPR_CORRECT("4.2 * 3.8", 15.96);
    ASSERT_EXPR_CORRECT("4.2 / 3.8", 4.2 / 3.8);
    ASSERT_EXPR_CORRECT("2 + 3 * 4", 14);
    ASSERT_EXPR_CORRECT("(2 + 3) * 4", 20);
    ASSERT_EXPR_CORRECT("3 / 0.00001", 300000);
    ASSERT_EXPR_CORRECT("0.00001 / 3", 0.00001 / 3);
    ASSERT_EXPR_CORRECT("-2 * (3 + 4)", -14);
    ASSERT_EXPR_CORRECT("-2 * (-3 + 4)", -2 * (-3 + 4));
    ASSERT_EXPR_CORRECT("-(2 * (3 + 4))", -14);
    ASSERT_EXPR_CORRECT("-2 ^ 3", -8);
    ASSERT_EXPR_CORRECT("2 ^ 3", 8);
    ASSERT_EXPR_CORRECT("-2 ^ -3", -0.125);
    ASSERT_EXPR_CORRECT("2 ^ -3", 0.125);
    ASSERT_EXPR_CORRECT(
        "4.6 * (8.8 - 100.64 / (25.22 + 49)) - (2.2 ^ 6)",
        4.6 * (8.8 - 100.64 / (25.22 + 49)) - (std::pow(2.2, 6)));
}