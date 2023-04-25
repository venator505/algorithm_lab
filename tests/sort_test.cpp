#include <algorithm>
#include <cstdlib>
#include <functional>
#include <vector>

#include "algorithm_lab/algorithm/sort/insertion_sort.h"
#include "algorithm_lab/algorithm/sort/quick_sort.h"
#include "gtest/gtest.h"

static const std::size_t kSmallArrSize = 100;
static const std::size_t kBigArrSize = 1e4;

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

    void assert_smallarr_sorted(std::function<void(std::vector<int>&)> f)
    {
        assert_sorted(f, small_vec);
    }

private:
    std::vector<int> small_vec;
    std::vector<int> big_vec;
    SortTester()
    {
        for (size_t i = 0; i < kBigArrSize; ++i) big_vec.push_back(rand());
        for (size_t i = 0; i < kSmallArrSize; ++i) small_vec.push_back(rand());
    }
};

TEST(insertion_sort, SmallArr)
{
    SortTester::instance().assert_smallarr_sorted(ybt::insertion_sort<int>);
}

TEST(quick_sort, SmallArr)
{
    SortTester::instance().assert_smallarr_sorted(ybt::quick_sort<int>);
}

TEST(insertion_sort, BigArr)
{
    SortTester::instance().assert_bigarr_sorted(ybt::insertion_sort<int>);
}

TEST(quick_sort, BigArr)
{
    SortTester::instance().assert_bigarr_sorted(ybt::quick_sort<int>);
}