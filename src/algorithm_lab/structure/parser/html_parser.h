#pragma once

#include "parser.h"
#include "html_lexer.h"
#include <iostream>
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
        HTMLTag tagInstance;
        match(HTMLToken::TAG_L);
        tagInstance.name = LV(0);
        match(HTMLToken::NAME);
        tagInstance.attras = attra_list();
        match(HTMLToken::TAG_R);
        if (LT(0) == HTMLToken::NAME)
        {
            tagInstance.content = LV(0);
            consume();
        }
        while (LT(0) == HTMLToken::TAG_L && LT(1) != HTMLToken::TAG_SLASH)
        {
            tagInstance.inner.push_back(tag());
        }

        match(HTMLToken::TAG_L);
        match(HTMLToken::TAG_SLASH);
        match(HTMLToken::NAME);
        match(HTMLToken::TAG_R);
        return tagInstance;
    }

    AttrabuitesMap attra_list()
    {
        AttrabuitesMap amap;
        while (LT(0) == HTMLToken::NAME)
        {
            std::string a_name = LV(0);
            std::string a_value;
            consume();
            match(HTMLToken::ASSIGN);
            if (LT(0) == HTMLToken::SQVALUE)
            {
                a_value = LV(0);
                match(HTMLToken::SQVALUE);
            }
            else if (LT(0) == HTMLToken::DQVALUE)
            {
                a_value = LV(0);
                match(HTMLToken::DQVALUE);
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