#include <algorithm>
#include <cstdlib>
#include <functional>
#include <vector>

#include "algorithm_lab/algorithm/sort/insertion_sort.h"
#include "gtest/gtest.h"

static const std::size_t kSmallArrSize = 100;

bool is_sorted(std::function<void(std::vector<int>&)> f, std::size_t arr_size)
{
    std::vector<int> user_arr(arr_size);
    for (std::size_t i = 0; i < arr_size; ++i) user_arr[i] = rand();
    std::vector<int> std_arr(user_arr);
    std::sort(std_arr.begin(), std_arr.end());
    f(user_arr);
    return user_arr == std_arr;
}

TEST(sort_test, insertion_sort)
{
    ASSERT_TRUE(is_sorted(ybt::insertion_sort<int>, kSmallArrSize));
}