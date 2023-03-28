#pragma once

#include <vector>

namespace ybt {
template <typename T>
void insertion_sort(std::vector<T>& vec)
{
    for (std::size_t i = 1; i < vec.size(); ++i)
    {
        T key = vec[i];
        for (std::size_t j = i - 1; j >= 0 && vec[j] > key; --j)
            std::swap(vec[j], vec[j + 1]);
    }
}
} // namespace ybt