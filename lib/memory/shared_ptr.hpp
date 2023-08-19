#pragma once

#include <vector>

#include <unique_ptr.hpp>
#include <weak_ptr.hpp>

template<typename T>
struct __control_block;

template<typename T>
class shared_ptr
{
    __control_block<T>* _cb_ptr;

    friend class weak_ptr<T>;

public:
    shared_ptr() : _cb_ptr() {}

    shared_ptr(T* data)
    {
        _cb_ptr = new __control_block<T>(data);
    }

    shared_ptr(unique_ptr<T>&& unique_ptr)
    {
        _cb_ptr = new __control_block<T>(unique_ptr.get());
        unique_ptr.release();
    }

    ~shared_ptr()
    {
        release();
    }

    shared_ptr(const shared_ptr& copy) : _cb_ptr(copy._cb_ptr)
    {
        if (_cb_ptr != nullptr)
        {
            _cb_ptr->add_shared();
        }
    }

    shared_ptr& operator=(T* data)
    {
        release();
        _cb_ptr = new __control_block<T>(data);
        return *this;
    }

    shared_ptr& operator=(const shared_ptr& copy)
    {
        if (this != &copy)
        {
            release();
            _cb_ptr = copy._cb_ptr;
            if (_cb_ptr != nullptr)
            {
                _cb_ptr->add_shared();
            }
        }
        return *this;
    }

    shared_ptr& operator=(unique_ptr<T>&& unique_ptr)
    {
        release();
        _cb_ptr = new __control_block<T>(unique_ptr.get());
        unique_ptr.release();
        return *this;
    }

    void release() noexcept
    {
        if (_cb_ptr != nullptr)
        {
            _cb_ptr->release_shared();
            _cb_ptr = nullptr;
        }
    }

    void reset()
    {
        T* tmp = release();
        delete tmp;
    }

    int use_count() const
    {
        if (_cb_ptr != nullptr)
        {
            return _cb_ptr->count();
        }
        return 0;
    }

    // Const correct access owned object
    T* operator->() const { return _cb_ptr->_data; }
    T& operator*()  const { return *_cb_ptr->_data; }

    // Access to smart pointer state
    T* get()                 const { return _cb_ptr->_data; }
    explicit operator bool() const { return _cb_ptr != nullptr; }

private:

    shared_ptr(__control_block<T>* cb) : _cb_ptr(cb)
    {
        if (_cb_ptr != nullptr)
        {
            _cb_ptr->add_shared();
        }
    }

};

template<typename T>
struct __control_block
{
    T*  _data;
    int _shared_count;
    int _weak_count;

    __control_block() : _data(nullptr), _shared_count(0), _weak_count(0) {}

    __control_block(T* data) : _data(data), _shared_count(1), _weak_count(0) {}

    void add_shared()
    {
        ++_shared_count;
    }

    void add_weak()
    {
        ++_weak_count;
    }

    void release_shared()
    {
        --_shared_count;
        release();
    }

    void release_weak()
    {
        --_weak_count;
        release();
    }

    int count ()
    {
        return _shared_count;
    }

    void release()
    {
        if (_shared_count <= 0)
        {
            delete _data;
            _data = nullptr;
        }
        if (_shared_count <= 0 && _weak_count <= 0)
        {
            delete this;
        }
    }
};