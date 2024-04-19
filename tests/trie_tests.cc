#include <gtest/gtest.h>
#include <trie.hpp>
#include <iostream>

using namespace ads;

TEST(TRIE, test_search_after_insert)
{
  Trie t;

  t.insert("ab");
  t.insert("a");
  t.insert("acd");

  ASSERT_FALSE(t.search("abb"));
  ASSERT_TRUE(t.search("a"));
  ASSERT_TRUE(t.search("acd"));
  ASSERT_TRUE(t.search("ab"));
  ASSERT_FALSE(t.search("acdx"));
};

TEST(TRIE, test_prefix)
{
  Trie t;
  t.insert("a");
  t.insert("abc");
  t.insert("bd");
  auto list = t.prefix("a");
  auto expr = std::is_same<decltype(list), std::list<std::string>>::value;

  ASSERT_TRUE(expr);
  ASSERT_TRUE(std::find(list.begin(), list.end(), "a") != list.end());
  ASSERT_TRUE(std::find(list.begin(), list.end(), "abc") != list.end());
  ASSERT_TRUE(std::find(list.begin(), list.end(), "bd") == list.end());
};
