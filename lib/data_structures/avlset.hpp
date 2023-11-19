#pragma once

#include "tree.hpp"

// AVL Adelson-Velsky and Landis

template<typename T>
class AvlSet : public Tree<T>
{
public:
    void push(const T& data_)
    {
        push_from(data_, this->_avlRoot, From::ROOT);
        Tree<T>::_root = _avlRoot;
    }

private:
    using Elem = typename Tree<T>::Elem;

    struct AvlElem : Elem
    {

        AvlElem(const T& data_) : _data(data_) {}

        const T& data() const override { return _data; }
        Elem* const left() const override { return _left; }
        Elem* const right() const override { return _right; }

        T _data;
        int _height = 1; // For AVL tree
        AvlElem* _left = nullptr;
        AvlElem* _right = nullptr;

        ~AvlElem() {}
    };

    AvlElem* _avlRoot = nullptr;

    enum class From
    {
        LEFT,
        RIGHT,
        ROOT
    };

    void push_from(const T& data_, AvlElem*& root_, From from_=From::NONE)
    {
        if (root_ == nullptr)
        {
            AvlElem* e = new AvlElem(data_);
            if (from_ == From::LEFT)
            {
                e->_right = root_;
            }
            else if (from_ == From::RIGHT)
            {
                e->_left = root_;
            }
            root_ = e;
        }
        else if (data_ == root_->_data)
        {
            return;
        }
        else if (data_ < root_->_data)
        {
            push_from(data_, root_->_left, From::LEFT);
            balance(root_);
        }
        else
        {
            push_from(data_, root_->_right, From::RIGHT);
            balance(root_);
        }
    }

    static void balance(AvlElem*& root_)
    {
        int bal_factor {difference(root_)};
        if (bal_factor > 1)
        {
            if (difference(root_->_left) > 0)
            {
                root_ = ll_rotation(root_);
            }
            else
            {
                root_ = lr_rotation(root_);
            }
        }
        else if (bal_factor < -1)
        {
            if (difference(root_->_right) > 0)
            {
                root_ = rl_rotation(root_);
            }
            else
            {
                root_ = rr_rotation(root_);
            }
        }
        return;
    }

    static int difference(AvlElem*& root_)
    {
        if (root_ == nullptr)
        {
            return 0;
        }

        return height(root_->_left) - height(root_->_right);
    }

    static size_t height(const AvlElem* const & root_)
    {
        if (root_ == nullptr)
        {
            return 0;
        }

        return 1 + std::max(height(root_->_left), height(root_->_right));
    }

    static AvlElem* rr_rotation(AvlElem*& root_)
    {
        AvlElem* res;
        res = root_->_right;
        root_->_right = res->_left;
        res->_left = root_;
        return res;
    }

    static AvlElem* ll_rotation(AvlElem*& root_)
    {
        AvlElem* res;
        res = root_->_left;
        root_->_left = res->_right;
        res->_right = root_;
        return res;
    }

    static AvlElem* lr_rotation(AvlElem*& root_)
    {
        AvlElem* res;
        res = root_->_left;
        root_->_left = rr_rotation(res);
        return ll_rotation(root_);
    }

    static AvlElem* rl_rotation(AvlElem*& root_)
    {
        AvlElem* res;
        res = root_->_right;
        root_->_right = ll_rotation(res);
        return rr_rotation(root_);
    }
};
