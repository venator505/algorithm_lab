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

    int get_type() const { return m_data->type; }

    std::string get_value() const { return m_data->value; }

    bool operator==(const Token& rhs) const { return *m_data == *rhs.m_data; }

protected:
    struct data
    {
        int type;
        std::string value;
        bool operator==(const data& rhs)
        {
            return type == rhs.type && value == rhs.value;
        }
        data(int type, const std::string& value) : type(type), value(value) {}
    };
    std::shared_ptr<data> m_data;
};
} // namespace parser
} // namespace structure
} // namespace ybt