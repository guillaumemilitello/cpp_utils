#pragma once

#include "tree.hpp"

template<typename T>
class Set : public Tree<T>
{
public:
    void push(const T& data_) override
    {
        push_from(data_, this->_root, From::ROOT);
    }

private:
    using Elem = typename Tree<T>::Elem;
    using From = typename Tree<T>::From;

    static void push_from(const T& data_, Elem*& root_, From from_)
    {
        if (root_ == nullptr)
        {
            Elem* e = new Elem(data_);
            if (from_ == From::LEFT)
            {
                e->right = root_;
            }
            else if (from_ == From::RIGHT)
            {
                e->left = root_;
            }
            root_ = e;
        }
        else
        {
            if (data_ == root_->data)
            {
                return;
            }
            else if (data_ < root_->data)
            {
                push_from(data_, root_->left, From::LEFT);
            }
            else
            {
                push_from(data_, root_->right, From::RIGHT);
            }
        }
    }
};
