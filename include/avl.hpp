/*
 * \brief  AVL tree
 * \author brfc
 * \date   2024-01-01
 */

/*
 * Copyright (C) 2024 R Carvalho
 *
 * This file is an AVL implementation,
 * which is distributed under the terms of the MIT License.
 *
 */

#pragma once

#include <memory>
#include <mutex>

namespace ads
{

template <typename T>
struct Node
{
    typedef std::unique_ptr<Node<T>> P_Node;

    T _data;
    int _balance;
    P_Node _right, _left;

    explicit Node(T d) : _data(d),
                         _balance(0),
                         _right(nullptr),
                         _left(nullptr){};

    template <typename U>
    friend bool operator==(const Node<U> &lhs, const Node<U> &rhs);
};

template <typename T>
class Tree
{
private:
    typedef std::unique_ptr<Node<T>> P_Node;

    std::mutex _mtx;

    P_Node root;

    int _get_balance(const P_Node &node) const noexcept
    {
        if (nullptr == node)
            return 0;
        return node->_balance;
    }

    P_Node _left_rotation(P_Node &root) const noexcept
    {
        P_Node right = std::move(root->_right);
        root->_right = std::move(right->_left);
        right->_left = std::move(root);

        right->_left->_balance =
            _get_balance(right->_left->_right) - _get_balance(right->_left->_left);
        right->_balance =
            _get_balance(right->_right) - _get_balance(right->_left);

        return right;
    };

    P_Node _right_rotation(P_Node &root) const noexcept
    {
        P_Node left = std::move(root->_left);
        root->_left = std::move(left->_right);
        left->_right = std::move(root);

        left->_right->_balance =
            _get_balance(left->_right->_right) - _get_balance(left->_right->_left);
        left->_balance =
            _get_balance(left->_right) - _get_balance(left->_left);

        return left;
    };

    P_Node _rightleft(P_Node &root) const noexcept
    {
        root->_left = _left_rotation(root->_left);
        return _right_rotation(root);
    }

    P_Node _leftright(P_Node &root) const noexcept
    {
        root->_right = _right_rotation(root->_right);
        return _left_rotation(root);
    }

    P_Node _balance(P_Node &tree) const noexcept
    {
        if (2 == tree->_balance)
        {
            if (tree->_right->_balance > 0)
                return _left_rotation(tree);
            else
                return _leftright(tree);
        }
        else if (-2 == tree->_balance)
        {
            if (tree->_left->_balance < 0)
                return _right_rotation(tree);
            else
                return _rightleft(tree);
        }

        return std::move(tree);
    };

    P_Node _insert(P_Node &root, const T &data) noexcept
    {
        if (!root)
        {
            root = std::make_unique<Node<T>>(data);
            return std::move(root);
        }

        if (data > root->_data)
        {
            root->_right = _insert(root->_right, data);
            root->_balance++;
        }
        else
        {
            root->_left = _insert(root->_left, data);
            root->_balance--;
        }

        root = _balance(root);
        return std::move(root);
    }

    bool _exist(const P_Node &node, const T &data) const noexcept
    {
        if (!node)
            return false;

        if (data == node->_data)
            return true;

        if (data > node->_data)
            return _exist(node->_right, data);

        return _exist(node->_left, data);
    }

    int _height(const P_Node &tree) const noexcept
    {
        if (nullptr == tree)
            return 0;

        return 1 + std::max(_height(tree->_left), _height(tree->_right));
    }

    int _size(const P_Node &tree) const noexcept
    {
        if (nullptr == tree)
            return 0;

        return 1 + _size(tree->_left) + _size(tree->_right);
    }

public:
    template <typename U>
    friend bool operator==(const Tree<U> &lhs, const Tree<U> &rhs);

    Tree() : 
        root(nullptr),
        _mtx()
    {};

    template <typename U, typename... Ts>
    Tree(T f_arg, U s_arg, Ts... args) : 
        root(nullptr)
    {
        static_assert(std::is_same<T, U>::value, 
            "[Error] Tree values need to have the same type.");
        insert(f_arg);
        insert(s_arg);
        (insert(args), ...);
    }

    int size() noexcept
    {
        std::lock_guard<std::mutex> lock(_mtx);
        return _size(root);
    }

    int height() noexcept
    {
        std::lock_guard<std::mutex> lock(_mtx);
        return _height(root);
    }

    bool exist(const T &d) noexcept
    {
        std::lock_guard<std::mutex> lock(_mtx);
        return _exist(root, d);
    }

    void insert(const T d) noexcept
    {
        std::lock_guard<std::mutex> lock(_mtx);
        root = _insert(root, d);
    }
};

template <typename U>
bool operator==(const Node<U> &lhs, const Node<U> &rhs)
{
    bool isEqualData = lhs._data == rhs._data;

    if (isEqualData)
    {
        if ((lhs._left == nullptr || rhs._left == nullptr) &&
            (lhs._right == nullptr || rhs._right == nullptr))
            return lhs._right == rhs._right && lhs._left == rhs._left;

        if (lhs._left == nullptr || rhs._left == nullptr)
            return *lhs._right == *rhs._right;

        if (lhs._right == nullptr || rhs._right == nullptr)
            return *lhs._left == *rhs._left;

        return *lhs._left == *rhs._left && *lhs._right == *rhs._right;
    }

    return false;
};

template <typename U>
bool operator==(const Tree<U> &lhs, const Tree<U> &rhs)
{
    if (lhs.root == nullptr || rhs.root == nullptr)
        return lhs.root == rhs.root;
    return *lhs.root == *rhs.root;
};

} // namespace ads
