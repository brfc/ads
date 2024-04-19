/*
 * \brief Segment Tree
 * \author brfc
 * \date 2024-04-17
 *
 * Copyright (C) 2024 R Carvalho
 *
 * This file is a segment tree implementation,
 * which is distributed under the terms of the MIT License.
 *
 */

#pragma once
#include <array>

namespace ads {

template <typename T, size_t N, typename Functor>
class SegmentTree
{
private:
    std::array<T, 4 * N> tree;
    Functor aggregator;

public:
    SegmentTree() = delete;

    void construct(const std::array<int, N> &arr,
                   unsigned int node,
                   unsigned int start,
                   unsigned int end) noexcept
    {
        if (start == end)
            tree[node] = arr[start];
        else
        {
            auto mid_index = (start + end) / 2;
            auto left_child = 2 * node;
            auto right_child = 2 * node + 1;

            construct(arr, left_child, start, mid_index);
            construct(arr, right_child, mid_index + 1, end);

            auto value_node = aggregator(tree[left_child], tree[right_child]);
            tree[node] = value_node;
        }
    }

    SegmentTree(std::array<int, N> &arr, Functor lambda) : tree(),
                                                           aggregator(lambda)
    {
        this->construct(arr, 1, 0, N - 1);
    };

    T get_value(
        unsigned int node_index,
        unsigned int start,
        unsigned int end,
        unsigned int from,
        unsigned int to)
    {
        auto mid = (start + end) / 2;
        auto left_child = 2 * node_index;
        auto right_child = 2 * node_index + 1;

        if (from == start && end == to)
            return tree[node_index];

        if (from > mid)
            return get_value(right_child, mid + 1, end, from, to);

        if (to <= mid)
            return get_value(left_child, start, mid, from, to);

        T left_value = get_value(left_child, start, mid, from, mid);
        T right_value = get_value(right_child, mid + 1, end, mid + 1, to);
        return aggregator(left_value, right_value);
    };

    T get_value(unsigned int from, unsigned int to)
    {
        if (from > to)
        {
            throw std::invalid_argument("Input values not allowed in get_value function (from > to).");
        }
        return get_value(1, 0, N - 1, from, to);
    }
};

} // namespace ads