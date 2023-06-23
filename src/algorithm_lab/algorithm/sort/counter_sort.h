#pragma once

#include <cstddef>
#include <vector>

namespace yyds {
template <typename T>
void counter_sort(std::vector<T>& vec, int q, int p)
{
    int range = p - q + 1;
    std::vector<T> hash_map(range, 0);
    // after this loop hash_map[i] = number i occure times in vec
    for (auto num : vec)
    {
        hash_map[num - q] += 1;
    }

    // after this loop hash_map[i] = the count that number <= vec[i]
    for (auto i = 1; i < range; ++i)
    {
        hash_map[i] += hash_map[i - 1];
    }

    std::vector<T> output(vec);

    for (int j = range - 1; j; --j)
    {
        output[hash_map[vec[j]] - 1] = vec[j];
        --hash_map[vec[j]];
    }

    vec = output;
}
} // namespace yyds