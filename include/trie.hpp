/*
 * \brief Prefix Tree
 * \author brfc
 * \date 2024-04-11
 *
 * Copyright (C) 2024 R Carvalho
 *
 * This file is a prefix tree implementation,
 * which is distributed under the terms of the MIT License.
 *
 */

#pragma once

#include <unordered_map>
#include <memory>
#include <list>

namespace ads
{

  struct Node
  {
    std::unordered_map<char, std::unique_ptr<Node>> children;
    bool is_word;

    Node(bool is_last_char) : children(),
                              is_word(is_last_char){};
  };

  class Trie
  {

    typedef std::unique_ptr<Node> P_Node;

  private:
    P_Node _root;

    P_Node _insert(P_Node &r, std::string &str) noexcept
    {
      if (str.empty())
        return std::move(r);
      auto head = str.at(0);
      auto tail = str.substr(1);
      auto is_word = tail.empty();

      if (r->children.find(head) != r->children.end())
      {
        if (is_word)
          r->children.at(head)->is_word = is_word;
        else
          r->children[head] = _insert(r->children.at(head), tail);
      }
      else
      {
        if (is_word)
          r->children[head] = std::make_unique<Node>(is_word);
        else
        {
          auto new_node = std::make_unique<Node>(false);
          r->children[head] = _insert(new_node, tail);
        }
      }

      return std::move(r);
    };

    bool _search(const P_Node &r, const std::string &str) const noexcept
    {
      if (str.empty())
        return r->is_word;
      auto head = str.at(0);
      auto tail = str.substr(1);
      return (r->children.find(head) != r->children.end()) && _search(r->children.at(head), tail);
    };

    std::list<std::string> _suffixes(const std::string &str, const P_Node &r) const
    {
      std::list<std::string> return_list;

      for (const auto &el : r->children)
      {
        std::string new_str = str + el.first;
        if (el.second->is_word)
          return_list.push_back(std::string(new_str));

        std::list<std::string> children_sufixes_list = _suffixes(new_str, el.second);
        return_list.merge(children_sufixes_list);
      }
      return return_list;
    };

  public:
    Trie() : _root(std::make_unique<Node>(false)){};

    void insert(const std::string &str)
    {
      auto mutable_string = str;
      if (mutable_string.empty())
        return;
      _root = _insert(_root, mutable_string);
    };

    bool search(const std::string &str) const
    {
      return _search(_root, str);
    };

    std::list<std::string> prefix(const std::string &str) const
    {
      Node *pointer = _root.get();
      std::unique_ptr<Node> *last_reference = nullptr;
      for (auto c : str)
      {
        auto it = pointer->children.find(c);
        if (it == pointer->children.end())
          break;
        pointer = it->second.get();
        last_reference = &(it->second);
      }

      std::list<std::string> return_list;
      if (pointer->is_word)
        return_list.push_back(str);

      return_list.merge(_suffixes(str, *last_reference));

      return return_list;
    };
  };

} // namespace ads
