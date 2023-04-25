#pragma once

#include <vector>

namespace ybt {
template <typename T>
void insertion_sort_impl(std::vector<T>& vec, int p, int q)
{
    if (p < q || p >= vec.size()) return;
    for (std::size_t i = p + 1; i <= q; ++i)
    {
        T key = vec[i];
        for (std::size_t j = i - 1; j >= 0 && vec[j] > key; --j)
            std::swap(vec[j], vec[j + 1]);
    }
}

template <typename T>
void insertion_sort(std::vector<T>& vec)
{
    insertion_sort_impl(vec, 0, vec.size() - 1);
}
} // namespace ybt