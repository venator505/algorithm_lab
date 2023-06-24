#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
namespace yyds {

template <typename KT, typename VT>
struct HashSlot
{
    KT key;
    VT value;
    bool bTaken = false;
    HashSlot(KT key = 0, VT value = 0) : key(key), value(value) {}
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
        map[index] = HashSlot<KT, VT>(key, value);
    }

    void remove(KT key)
    {
        auto exsistAndIndex = search(key);
        if (exsistAndIndex.first)
            map[exsistAndIndex.second].bTaken = false;
        else
            throw std::runtime_error("key:" + std::to_string(key) +
                                     " dont't exsist in hashtable");
    }

    VT& operator[](KT key)
    {
        auto exsistAndIndex = search(key);
        if (exsistAndIndex.first) return map[exsistAndIndex.second].value;
        throw std::runtime_error("key:" + std::to_string(key) +
                                 " dont't exsist in hashtable");
    }

    std::pair<bool, std::size_t> search(KT key)
    {
        size_t index;
        size_t try_times = 0;
        //线性探查,直到找到目标
        for (index = hash(key), try_times = 0;
             map[index].key != key && map[index].bTaken &&
             try_times < map.size();
             ++index, ++try_times)
            ;
        if (map[index].key == key)
            return {true, index};
        else
            return {false, 0};
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