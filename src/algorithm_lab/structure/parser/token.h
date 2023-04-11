#pragma once

#include <memory>
#include <string>

namespace ybt {
namespace structure {
namespace parser {
class Token
{
public:
    Token(int type, const std::string value) : m_data(new data(type, value)) {}
    int get_type() { return m_data->type; }
    std::string get_value() { return m_data->value; }

protected:
    struct data
    {
        int type;
        std::string value;
        data(int type, const std::string& value) : type(type), value(value) {}
    };
    std::shared_ptr<data> m_data;
};
} // namespace parser
} // namespace structure
} // namespace ybt