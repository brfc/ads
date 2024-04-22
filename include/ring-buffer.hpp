/*
 * \brief Ring Buffer
 * \author brfc
 * \date 2024-04-09
 *
 * Copyright (C) 2024 R Carvalho
 *
 * This file is a circular _buffer implementation,
 * which is distributed under the terms of the MIT License.
 *
 */

#pragma once

#include <optional>
#include <mutex>

namespace ads{

template <typename T, size_t N>
class RingBuffer
{
private:
  std::mutex _mtx;
  T _buffer[N];
  uint _head, _tail;

  inline uint _next(const uint &index) const noexcept
  {
    return (index + 1) % N;
  }
public:
  bool is_empty, is_full;
  RingBuffer() : _mtx(),
                 _buffer(),
                 _head(0),
                 _tail(0),
                 is_empty(true),
                 is_full(false){};

  inline uint size(void) const noexcept
  {
    if (_head == _tail)
      return 0;
    if (_tail > _head)
      return _tail - _head;
    else
      return N - (_head - _tail);
  }

  void write(const T &elem) noexcept
  {
    std::lock_guard<std::mutex> lock(_mtx);
    _buffer[_tail] = elem;
    _tail = _next(_tail);

    if (_head == _tail)
      is_full = true;
    is_empty = false;
  }

  std::optional<T> read(void) noexcept
  {
    std::lock_guard<std::mutex> lock(_mtx);
    if (is_empty)
      return std::nullopt;

    auto ret_value = std::optional<T>(_buffer[_head]);
    _head = _next(_head);

    is_full = false;

    if (_head == _tail) is_empty = true;
    
    return ret_value;
  }
};

} //namespace ads
