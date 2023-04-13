#pragma once
#include <cstdint>
#include <stdexcept>
#include "lexer.h"
#include "token.h"
namespace ybt {
namespace structure {
namespace parser {
class Parser
{
public:
    Parser(Lexer* input, const uint8_t k = 1)
        : input(input), tokens(new Token[k]), k(k), p(0)
    {
        for (int i = 0; i < k; ++i) consume();
    }

    void consume()
    {
        tokens[p] = input->nextToken();
        p = (p + 1) % k;
    }

    void match(int type)
    {
        if (LT(0) == type)
        {
            consume();
        }
        else
        {
            throw std::runtime_error(std::string("invaildType"));
        }
    }

    int LT(const size_t kth) { return tokens[(p + kth) % k].get_type(); }

    const std::string& LV(const size_t kth)
    {
        return tokens[(p + kth) % k].get_value();
    }

protected:
    Lexer* input = nullptr;
    Token* tokens;
    const uint8_t k;
    int p;
};
} // namespace parser
} // namespace structure
} // namespace ybt