#pragma once

#include <string>

namespace ybt {
namespace structure {
namespace parser {
class Token
{
public:
    Token(int type, const std::string value) : type(type), value(value) {}
    int get_type() { return type; }
    std::string get_value() { return value; }

protected:
    int type;
    std::string value;
};
} // namespace parser
} // namespace structure
} // namespace ybt