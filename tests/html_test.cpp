#include <gtest/gtest.h>

#include "algorithm_lab/structure/parser/html_lexer.h"
#include "algorithm_lab/structure/parser/html_parser.h"
#include "algorithm_lab/structure/parser/token.h"

using namespace ybt::structure::parser;

TEST(HTML, lexer)
{
    std::string html = "<a class=\"test\"></a>";
    HtmlLexer lexer(html);
    std::vector<Token> vec{
        {HTMLToken::TAG_L, "<"},    {HTMLToken::NAME, "a"},
        {HTMLToken::NAME, "class"}, {HTMLToken::ASSIGN, "="},
        {HTMLToken::DQUOTE, "\""},  {HTMLToken::NAME, "test"},
        {HTMLToken::DQUOTE, "\""},  {HTMLToken::TAG_R, ">"},
        {HTMLToken::TAG_L, "<"},    {HTMLToken::TAG_SLASH, "/"},
        {HTMLToken::NAME, "a"},     {HTMLToken::TAG_R, ">"}};
    auto t = lexer.nextToken();
    for (size_t i = 0; i < vec.size() && t.get_type() != EOF;
         ++i, t = lexer.nextToken())
    {
        ASSERT_EQ(t.get_type(), vec[i].get_type());
    }
}

TEST(HTML, Parser)
{
    std::string html = "<html>"
                       "<head>"
                       "<title>thisisatestpage</title>"
                       "</head>"
                       "<body>"
                       "<h1>welcometomypage</h1>"
                       "<p>thisisatestp</p>"
                       "<ul>"
                       "<li>test1</li>"
                       "<li>test2</li>"
                       "<li>test3</li>"
                       "</ul>"
                       "</body> </html>";
    HtmlLexer lexer(html);
    HTMLParser parser(&lexer);
    parser.tag();
}