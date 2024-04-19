#include <gtest/gtest.h>
#include <segment-tree.hpp>
#include <iostream>

using namespace ads;

TEST(SEGMENT_TREE, test_get_value_from_to)
{
    auto aggregator_function = [](int x, int y) -> int
    {
        return x + y;
    };

    std::array<int, 4> arr = {1, 1, 1, 1};
    SegmentTree<int, 4, decltype(aggregator_function)> s(arr, aggregator_function);

    auto value_1 = s.get_value(0, 0);
    auto value_4 = s.get_value(0, 3);
    auto value_2 = s.get_value(2, 3);

    auto value = s.get_value(1, 2);

    ASSERT_EQ(value_1, 1);
    ASSERT_EQ(value_4, 4);
    ASSERT_EQ(value_2, 2);
    ASSERT_EQ(value, 2);
}
