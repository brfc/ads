#include <gtest/gtest.h>
#include <ring-buffer.hpp>
#include <iostream>

using namespace std;
using namespace ads;

TEST(RING_BUFFER_TESTS, test_empty)
{
  RingBuffer<int, 10> r;

  ASSERT_EQ(r.size(), 0);
  ASSERT_FALSE(r.is_full);
};

TEST(RING_BUFFER_TESTS, test_write)
{
  RingBuffer<int, 10> r;

  r.write(1);
  r.write(1);
  r.write(1);

  ASSERT_EQ(r.size(), 3);
};

TEST(RING_BUFFER_TESTS, test_write_overflow)
{
  RingBuffer<int, 3> r;

  r.write(1);
  r.write(2);
  r.write(3);

  ASSERT_TRUE(r.is_full);
};

TEST(RING_BUFFER_TESTS, test_write_overflow_2)
{
  RingBuffer<int, 3> r;

  r.write(1);
  r.write(2);
  r.write(3);
  r.write(4);

  ASSERT_TRUE(r.is_full);
};

TEST(RING_BUFFER_TESTS, test_read_empty)
{
  RingBuffer<int, 2> r;
  ASSERT_EQ(r.read(), std::nullopt);
};

TEST(RING_BUFFER_TESTS, test_read_after_write)
{
  RingBuffer<int, 2> r;
  r.write(1);
  r.write(2);

  auto v1 = r.read();
  auto v2 = r.read();

  ASSERT_EQ(v1.value(), 1);
  ASSERT_EQ(v2.value(), 2);
};
