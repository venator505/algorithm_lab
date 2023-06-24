#include <algorithm>
#include <vector>
#include "algorithm_lab/structure/hash_table.h"
#include "gtest/gtest.h"
TEST(HashTable, insert)
{
    yyds::HashTable<int, int> hashtable;
    hashtable.insert(1, 6);
    hashtable.insert(3, 9);
    hashtable.insert(114, 514);
    hashtable.insert(985, 211);
    ASSERT_EQ(hashtable[1], 6);
    ASSERT_EQ(hashtable[3], 9);
    ASSERT_EQ(hashtable[114], 514);
    ASSERT_EQ(hashtable[985], 211);
}

TEST(HashTable, remove)
{
    yyds::HashTable<int, int> hashtable;
    hashtable.insert(114, 514);
    hashtable.insert(985, 211);
    ASSERT_EQ(hashtable[114], 514);
    ASSERT_EQ(hashtable[985], 211);
    hashtable.remove(114);
}
