#include <algorithm>
#include <vector>
#include "algorithm_lab/structure/binary_tree.h"
#include "gtest/gtest.h"

TEST(BinaryTree, Insert)
{
    yyds::BinaryTree<int> tree;
    tree.insert(406);
    tree.insert(1010);
    tree.insert(8);
    tree.insert(34);
    tree.insert(-1);
    for (int i = 45; i > 10; i -= 4) tree.insert(i);
    tree.inorder_walk();
}

TEST(BinaryTree, MaxAndMin)
{
    yyds::BinaryTree<int> tree;
    tree.insert(406);
    tree.insert(1010);
    tree.insert(8);
    tree.insert(34);
    tree.insert(-1);
    for (int i = 45; i > 10; i -= 4) tree.insert(i);
    ASSERT_EQ(tree.max()->val, 1010);
    ASSERT_EQ(tree.min()->val, -1);
}

TEST(BinaryTree, Remove)
{
    yyds::BinaryTree<int> tree;
    tree.insert(406);
    tree.insert(1010);
    tree.insert(8);
    tree.insert(34);
    tree.insert(-1);
    ASSERT_TRUE(tree.search(406)->val == 406);
    tree.remove(406);
    ASSERT_TRUE(tree.search(406) == nullptr);
}