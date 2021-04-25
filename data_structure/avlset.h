#pragma once

#include "tree.hpp"

// AVL Adelson-Velsky and Landis

template<typename T>
class AvlSet : public Tree<T>
{
public:
    void push(const T& data_)
    {
        push_from(data_, this->_root, From::ROOT);
    }

private:
    using Elem = typename Tree<T>::Elem;
    using From = typename Tree<T>::From;

    static void push_from(const T& data_, Elem*& root_, From from_=From::NONE)
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
        else if (data_ == root_->data)
        {
            return;
        }
        else if (data_ < root_->data)
        {
            push_from(data_, root_->left, From::LEFT);
            balance(root_);
        }
        else
        {
            push_from(data_, root_->right, From::RIGHT);
            balance(root_);
        }
    }

    static void balance(Elem*& root_)
    {
        int bal_factor {difference(root_)};
        if (bal_factor > 1)
        {
            if (difference(root_->left) > 0)
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
            if (difference(root_->right) > 0)
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

    static int difference(Elem*& root_)
    {
        if (root_ == nullptr)
        {
            return 0;
        }

        return height(root_->left) - height(root_->right);
    }

    static size_t height(const Elem* const & root_)
    {
        if (root_ == nullptr)
        {
            return 0;
        }

        return 1 + std::max(height(root_->left), height(root_->right));
    }

    static Elem* rr_rotation(Elem*& root_)
    {
        Elem* res;
        res = root_->right;
        root_->right = res->left;
        res->left = root_;
        return res;
    }

    static Elem* ll_rotation(Elem*& root_)
    {
        Elem* res;
        res = root_->left;
        root_->left = res->right;
        res->right = root_;
        return res;
    }

    static Elem* lr_rotation(Elem*& root_)
    {
        Elem* res;
        res = root_->left;
        root_->left = rr_rotation(res);
        return ll_rotation(root_);
    }

    static Elem* rl_rotation(Elem*& root_)
    {
        Elem* res;
        res = root_->right;
        root_->right = ll_rotation(res);
        return rr_rotation(root_);
    }
};
