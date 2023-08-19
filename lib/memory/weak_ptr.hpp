#pragma once

#include <shared_ptr.hpp>

template<typename T>
struct __control_block;

template<typename T> class shared_ptr;

template<typename T>
class weak_ptr
{
    __control_block<T>* _cb_ptr;

public:
    weak_ptr() : _cb_ptr() {}

    weak_ptr(const shared_ptr<T>& shared_ptr) : _cb_ptr(shared_ptr._cb_ptr)
    {
        if (_cb_ptr != nullptr)
        {
            _cb_ptr->add_weak();
        }
    }

    weak_ptr& operator=(const shared_ptr<T>& shared_ptr)
    {
        _cb_ptr = shared_ptr._cb_ptr;
        if (_cb_ptr != nullptr)
        {
            _cb_ptr->add_weak();
        }
        return *this;
    }

    shared_ptr<T> lock() const
    {
        if (!expired())
        {
            return shared_ptr<T>(_cb_ptr);
        }
        return shared_ptr<T>();
    }

    ~weak_ptr()
    {
        reset();
    }

    void reset()
    {
        if (_cb_ptr != nullptr)
        {
            _cb_ptr->release_weak();
        }
    }

    int use_count() const
    {
        if (_cb_ptr != nullptr)
        {
            return _cb_ptr->count();
        }
        return 0;
    }

    bool expired() const { return use_count() == 0; }
};