/*
 * \brief Ring Buffer
 * \author brfc
 * \date 2024-04-09
 *
 * Copyright (C) 2024 R Carvalho
 *
 * This file is a circular buffer implementation,
 * which is distributed under the terms of the MIT License.
 *
 */

#pragma once

#include <optional>

template <typename T, size_t N>
class RingBuffer
{
private:
  T buffer[N];
  uint head, tail;

  inline uint next(const uint &index) const noexcept
  {
    return (index + 1) % N;
  }
public:
  bool is_empty, is_full;
  RingBuffer() : head(0),
                 tail(0),
                 is_empty(true),
                 is_full(false){};

  inline uint size(void) const noexcept
  {
    if (head == tail)
      return 0;
    if (tail > head)
      return tail - head;
    else
      return N - (head - tail);
  }

  void write(const T &elem) noexcept
  {
    buffer[tail] = elem;
    tail = next(tail);

    if (head == tail)
      is_full = true;
    is_empty = false;
  }

  std::optional<T> read(void) noexcept
  {
    if (is_empty)
      return std::nullopt;

    auto ret_value = std::optional<T>(buffer[head]);
    head = next(head);

    is_full = false;

    if (head == tail) is_empty = true;
    
    return ret_value;
  }
};
