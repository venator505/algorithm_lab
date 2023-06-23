#include <algorithm>
#include <vector>
#include "algorithm_lab/algorithm/sort/counter_sort.h"
#include "gtest/gtest.h"
TEST(counter_sort, RangedArr)
{
    std::vector<int> vec{0, 5, 9, 6, 2, 3, 1, 1};
    std::vector<int> tmp(vec);
    std::sort(tmp.begin(), tmp.end());
    yyds::counter_sort(vec, 0, 9);
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
    ASSERT_EQ(vec, tmp);
}