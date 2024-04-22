#include <gtest/gtest.h>
#include <cmath>
#include <avl.hpp>
#include <thread>


using namespace std;
using namespace ads;

class AVL : public ::testing::Test
{
protected:
    void SetUp() override {};
    void TearDown() override {};

public:
    template <typename T>
    bool balanced(Tree<T> &t)
    {
        auto size = t.size();
        auto height = t.height();

        auto p = height < 1.44 * log2(size);

        return p;
    };
};

TEST_F(AVL, ASSIGNMENT)
{
    Tree<int> tree;
    tree.insert(0);

    Tree<int> *tree_copy;
    tree_copy = &tree;

    ASSERT_TRUE(tree_copy->exist(0));
    ASSERT_FALSE(tree_copy->exist(1));
};

TEST_F(AVL, INSERT_ROTATION_L)
{
    Tree<int> tree{0, 1, 2};

    ASSERT_EQ(tree.size(), 3);
    ASSERT_TRUE(balanced(tree));
};

TEST_F(AVL, INSERT_ROTATION_R)
{
    Tree<int> tree{0, -1, 2};

    ASSERT_EQ(tree.size(), 3);
    ASSERT_TRUE(balanced(tree));
};

TEST_F(AVL, INSERT_ROTATION_RL)
{
    Tree<int> tree{1, 3, 2};

    ASSERT_EQ(tree.size(), 3);
    ASSERT_EQ(tree.height(), 2);
    ASSERT_TRUE(balanced(tree));
};

TEST_F(AVL, INSERT_ROTATION_LR)
{
    Tree<int> tree{0, -3, -1};

    ASSERT_EQ(tree.size(), 3);
    ASSERT_EQ(tree.height(), 2);
    ASSERT_TRUE(balanced(tree));
};

TEST_F(AVL, EXIST_CASE1)
{
    Tree<int> tree{0, 1, 2, 3};

    ASSERT_TRUE(tree.exist(3));
    ASSERT_FALSE(tree.exist(100));
};

TEST_F(AVL, EXIST_CASE2)
{
    Tree<int> tree{5, 4, 3, 2, 1, 0, 1, 2, 3};

    ASSERT_TRUE(tree.exist(5));
    ASSERT_FALSE(tree.exist(100));
};

TEST_F(AVL, EXIST_CASE3)
{
    Tree<int> tree{5, 10, 2, 4};

    ASSERT_TRUE(tree.exist(4));
};

TEST_F(AVL, EQUALITY)
{
    Tree<int> tree{1, 2, 3, 4, 5};
    Tree<int> tree2{1, 2, 3, 4, 5};
    Tree<int> tree3{1, 2, 3};

    ASSERT_TRUE(tree == tree2);
    ASSERT_FALSE(tree2 == tree3);
}

TEST_F(AVL, EQUALITY_FAULT)
{
    Tree<int> tree4{1, 2};
    Tree<int> tree5;

    ASSERT_FALSE(tree4 == tree5);
}

TEST_F(AVL, CONCURRENCY_INSERT)
{
  Tree<int> tree{213,23143,565,767,842,1,23234,5431,-1239};
  const int initial_size = tree.size();

  // start 1000 threads * insert op
  const int num_threads = 1000;
  std::thread t[num_threads];
  for(int i = 0 ; i < num_threads ; i++)
    t[i] = std::thread(&Tree<int>::insert, &tree, 2);
    
  for(int i = 0 ; i < num_threads ; i++)
    t[i].join();

  ASSERT_EQ(tree.size() , initial_size + num_threads);
}
