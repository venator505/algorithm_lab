#pragma once

#include <cstddef>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
namespace yyds {

class KeyNotExistException : public std::exception
{
public:
    KeyNotExistException(std::size_t key)
        : message(("Key not found: ") + std::to_string(key))
    {
    }

    KeyNotExistException(const char* key)
        : message(("Key not found: ") + std::string(key))
    {
    }

    KeyNotExistException(const std::string& key)
        : message(("Key not found: ") + (key))
    {
    }

    const char* what() const noexcept override { return message.c_str(); }

private:
    std::string message;
};

template <typename KT, typename VT>
struct HashSlot
{
    KT key;
    VT value;
    bool bTaken = false;
    HashSlot(KT key = 0, VT value = 0, bool taken = false)
        : key(key), value(value), bTaken(taken)
    {
    }
};

template <typename KT, typename VT>
class HashTable
{
public:
    // TODO 支持动态扩张
    HashTable(size_t initSize = 16) { map.resize(initSize); }

    void insert(KT key, VT value)
    {
        size_t index;
        size_t try_times = 0;
        //线性探查,直到找到一个合适的位置.
        for (index = hash(key), try_times = 0;
             map[index].bTaken && try_times < map.size(); ++index, ++try_times)
            ;
        map[index] = HashSlot<KT, VT>(key, value, true);
    }

    void remove(KT key)
    {
        auto index = search(key);
        map[index].bTaken = false;
    }

    VT& operator[](KT key)
    {
        std::size_t index = search(key);
        return map[index].value;
    }

    std::size_t search(KT key)
    {
        size_t index;
        size_t try_times = 0;
        //线性探查,直到找到目标
        for (index = hash(key), try_times = 0;
             map[index].key != key && try_times < map.size();
             ++index, ++try_times)
            ;
        if (map[index].key == key && map[index].bTaken) return index;
        throw KeyNotExistException(key);
    }

private:
    std::vector<HashSlot<KT, VT>> map;

    std::size_t hash(const std::size_t key) { return key % map.size(); }

    std::size_t hash(const std::string& str)
    {
        size_t total = 0;
        for (size_t i = 0; i < str.size(); ++i)
        {
            total += static_cast<std::size_t>(str[i] - 'A');
        }
        return total;
    }
};
} // namespace yyds