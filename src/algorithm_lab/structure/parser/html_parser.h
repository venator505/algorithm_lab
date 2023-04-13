#pragma once

#include "parser.h"
#include "html_lexer.h"
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace ybt {
namespace structure {
namespace parser {

struct HTMLAttribute
{
    std::string key;
    std::string value;
};

using AttrabuitesMap = std::vector<HTMLAttribute>;

struct HTMLTag
{
    std::string name;
    std::string content;
    std::vector<HTMLTag> inner;
    AttrabuitesMap attras;
};

class HTMLParser : public Parser
{
public:
    HTMLParser(HtmlLexer* input) : Parser(input, 2) {}

    HTMLTag tag()
    {
        std::string name, content;
        std::vector<HTMLTag> inner;
        match(HTMLToken::TAG_L);
        name = LV(0);
        match(HTMLToken::NAME);
        auto attras = std::move(attra_list());
        match(HTMLToken::TAG_R);
        if (LT(0) == HTMLToken::NAME)
        {
            content = LV(0);
            consume();
        }
        while (LT(0) == HTMLToken::TAG_L && LT(1) != HTMLToken::TAG_SLASH)
        {
            inner.push_back(tag());
        }

        match(HTMLToken::TAG_L);
        match(HTMLToken::TAG_SLASH);
        match(HTMLToken::NAME);
        match(HTMLToken::TAG_R);
        return HTMLTag{name, content, inner, attras};
    }

    AttrabuitesMap attra_list()
    {
        AttrabuitesMap amap = AttrabuitesMap();
        while (LT(0) == HTMLToken::NAME)
        {
            std::string a_name = LV(0);
            std::string a_value;
            consume();
            match(HTMLToken::ASSIGN);
            if (LT(0) == HTMLToken::SQUOTE)
            {
                consume();
                a_value = LV(0);
                match(HTMLToken::NAME);
                match(HTMLToken::SQUOTE);
            }
            else if (LT(0) == HTMLToken::DQUOTE)
            {
                consume();
                a_value = LV(0);
                match(HTMLToken::NAME);
                match(HTMLToken::DQUOTE);
            }
            else
            {
                throw std::runtime_error("ExpectedQuote");
            }
            amap.push_back(HTMLAttribute{a_name, a_value});
        }
        return amap;
    }

private:
    HTMLTag content;
};
} // namespace parser
} // namespace structure
} // namespace ybt