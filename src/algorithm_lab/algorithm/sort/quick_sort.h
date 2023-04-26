#pragma once

#include <cstdlib>
#include <vector>
#include "insertion_sort.h"
namespace ybt {

template <typename T>
static int partition(std::vector<T>& vec, int p, int q)
{
    int key = vec[q];
    int i = p - 1, j = p;
    // split the array to three area : < = >
    // a[p..i] < key
    // a[j..q] > key
    while (j < q)
    {
        // countering a vector swap
        if (vec[j] <= key)
        {
            std::swap(vec[j], vec[++i]);
        }
        ++j;
    }
    std::swap(vec[i + 1], vec[q]);
    return i + 1;
}

template <typename T>
static int random_partition(std::vector<T>& vec, int p, int q)
{
    int key = p + rand() % (q - p);
    std::swap(vec[key], vec[q]);
    return partition(vec, p, q);
}

template <typename T>
static void quick_sort_impl(std::vector<T>& vec, int p, int q)
{
    if (p < q)
    {
        int r = partition(vec, p, q);
        quick_sort_impl(vec, p, r - 1);
        quick_sort_impl(vec, r + 1, q);
    }
}

template <typename T>
static void quick_sort_stl_impl(std::vector<T>& vec, int p, int q)
{
    if (q - p >= 15)
    {
        int r = random_partition(vec, p, q);
        quick_sort_impl(vec, 0, r - 1);
        quick_sort_impl(vec, r + 1, q);
    }
    else
    {
        insertion_sort_impl(vec, p, q);
    }
}

template <typename T>
void quick_sort(std::vector<T>& vec)
{
    quick_sort_impl(vec, 0, vec.size() - 1);
}

template <typename T>
void quick_sort_stl(std::vector<T>& vec)
{
    quick_sort_stl_impl(vec, 0, vec.size() - 1);
}

} // namespace ybt