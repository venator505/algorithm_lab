#include <algorithm>
#include <cstdlib>
#include <functional>
#include <vector>

#include "algorithm_lab/algorithm/sort/insertion_sort.h"
#include "algorithm_lab/algorithm/sort/quick_sort.h"
#include "algorithm_lab/algorithm/sort/shell_sort.h"
#include "gtest/gtest.h"

static const std::size_t kBigArrSize = 1e5;

class SortTester
{
public:
    static SortTester& instance()
    {
        static SortTester inst;
        return inst;
    }

    void assert_sorted(std::function<void(std::vector<int>&)> f,
                       std::vector<int>& vec)
    {
        std::vector<int> user(vec), stl(vec);
        std::sort(stl.begin(), stl.end());
        f(user);
        ASSERT_EQ(user, stl);
    }

    void assert_bigarr_sorted(std::function<void(std::vector<int>&)> f)
    {
        assert_sorted(f, big_vec);
    }

    void assert_sortedarr_sorted(std::function<void(std::vector<int>&)> f)
    {
        assert_sorted(f, sorted_vec);
    }

private:
    std::vector<int> big_vec;
    std::vector<int> sorted_vec;
    SortTester()
    {
        for (size_t i = 0; i < kBigArrSize; ++i) big_vec.push_back(rand());
        for (size_t i = 0; i < kBigArrSize / 10; ++i) sorted_vec.push_back(i);
    }
};

TEST(insertion_sort, BigArr)
{
    SortTester::instance().assert_bigarr_sorted(ybt::insertion_sort<int>);
}

TEST(insertion_sort, SortedArr)
{
    SortTester::instance().assert_sortedarr_sorted(ybt::insertion_sort<int>);
}

TEST(quick_sort, BigArr)
{
    SortTester::instance().assert_bigarr_sorted(ybt::quick_sort<int>);
}

TEST(quick_sort, SortedArr)
{
    SortTester::instance().assert_sortedarr_sorted(ybt::quick_sort<int>);
}

TEST(quick_sort_stl, BigArr)
{
    SortTester::instance().assert_bigarr_sorted(ybt::quick_sort_stl<int>);
}

TEST(quick_sort_stl, SortedArr)
{
    SortTester::instance().assert_sortedarr_sorted(ybt::quick_sort_stl<int>);
}

TEST(shell_sort, BigArr)
{
    SortTester::instance().assert_bigarr_sorted(ybt::shell_sort<int>);
}

TEST(stl_sort, BigArr)
{
    auto f = [](std::vector<int>& v) { std::sort(v.begin(), v.end()); };
    SortTester::instance().assert_bigarr_sorted(f);
}

TEST(stl_sort, SortedArr)
{
    auto f = [](std::vector<int>& v) { std::sort(v.begin(), v.end()); };
    SortTester::instance().assert_bigarr_sorted(f);
}