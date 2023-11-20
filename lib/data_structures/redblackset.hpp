#pragma once

#include "tree.hpp"

// Red Black

template<typename T>
class RedBlackSet : public Tree<T>
{
public:
    void push(const T& data_)
    {
        push(data_, _redBlackRoot);
        Tree<T>::_root = _redBlackRoot;
    }

private:
    using Elem = typename Tree<T>::Elem;

    enum Color { Red, Black };

    struct RedBlackElem : Elem
    {
        RedBlackElem(const T& data_) : _data(data_) {}

        const T& data() const override { return _data; }
        Elem* const left() const override { return _left; }
        Elem* const right() const override { return _right; }


        T _data;
        Color _color = Color::Red;
        RedBlackElem* _left = nullptr;
        RedBlackElem* _right = nullptr;
        RedBlackElem* _parent = nullptr;

        ~RedBlackElem() {}
    };

    RedBlackElem* _redBlackRoot = nullptr;

    void push(const T& data_, RedBlackElem*& root_)
    {
        RedBlackElem* z = new RedBlackElem(data_);
        RedBlackElem* y = nullptr;
        RedBlackElem* x = _redBlackRoot;

        // Find the position to insert the new elem
        while (x != nullptr)
        {
            y = x;
            if (z->_data < x->_data)
            {
                x = x->_left;
            }
            else if (z->_data == x->_data)
            {
                return;
            }
            else
            {
                x = x->_right;
            }
        }

        // Insert the new node into the tree
        z->_parent = y;
        if (y == nullptr)
        {
            _redBlackRoot = z;
        }
        else if (z->_data < y->_data)
        {
            y->_left = z;
        }
        else
        {
            y->_right = z;
        }

        // Fix the Red-Black tree properties after insertion
        recolor(z);
    }

    void recolor(RedBlackElem* z)
    {
        while (z->_parent != nullptr && z->_parent->_color == Color::Red)
        {
            if (z->_parent == z->_parent->_parent->_left)
            {
                RedBlackElem* y = z->_parent->_parent->_right;

                // Case 1: Both parent and uncle are red
                if (y != nullptr && y->_color == Color::Red)
                {
                    z->_parent->_color = Color::Black;
                    y->_color = Color::Black;
                    z->_parent->_parent->_color = Color::Red;
                    z = z->_parent->_parent;
                }
                else // Case 2: Parent is red, but uncle is black
                {
                    if (z == z->_parent->_right)
                    {
                        z = z->_parent;
                        leftRotate(z);
                    }
                    // Case 3: Parent is red, uncle is black, and z is a left child
                    z->_parent->_color = Color::Black;
                    z->_parent->_parent->_color = Color::Red;
                    rightRotate(z->_parent->_parent);
                }
            }
            else
            {
                RedBlackElem* y = z->_parent->_parent->_left;

                // Case 1: Both parent and uncle are red
                if (y != nullptr && y->_color == Color::Red)
                {
                    z->_parent->_color = Color::Black;
                    y->_color = Color::Black;
                    z->_parent->_parent->_color = Color::Red;
                    z = z->_parent->_parent;
                }
                else // Case 2: Parent is red, but uncle is black
                {
                    if (z == z->_parent->_left)
                    {
                        z = z->_parent;
                        rightRotate(z);
                    }
                    // Case 3: Parent is red, uncle is black, and z is a left child
                    z->_parent->_color = Color::Black;
                    z->_parent->_parent->_color = Color::Red;
                    leftRotate(z->_parent->_parent);
                }
            }
        }
        _redBlackRoot->_color = Color::Black;
    }

    void leftRotate(RedBlackElem* x)
    {
        RedBlackElem* y = x->_right;
        x->_right = y->_left;
        if (y->_left != nullptr)
        {
            y->_left->_parent = x;
        }
        y->_parent = x->_parent;
        if (x->_parent == nullptr)
        {
            _redBlackRoot = y;
        }
        else if (x == x->_parent->_left)
        {
            x->_parent->_left = y;
        }
        else
        {
            x->_parent->_right = y;
        }
        y->_left = x;
        x->_parent = y;
    }

    void rightRotate(RedBlackElem* y)
    {
        RedBlackElem* x = y->_left;
        y->_left = x->_right;
        if (x->_right != nullptr)
        {
            x->_right->_parent = y;
        }
        x->_parent = y->_parent;
        if (y->_parent == nullptr)
        {
            _redBlackRoot = x;
        }
        else if (y == y->_parent->_left)
        {
            y->_parent->_left = x;
        }
        else
        {
            y->_parent->_right = x;
        }
        x->_right = y;
        y->_parent = x;
    }
};
