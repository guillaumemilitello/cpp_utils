#pragma once

#include <unique_ptr.hpp>

template<typename T>
class shared_ptr
{
    T*   data;
    int* count;

public:
    shared_ptr() : data(nullptr), count(nullptr) {}

    shared_ptr(T* data) : data(data), count(new int(1)) {}

    shared_ptr(unique_ptr<T>&& unique_ptr) : count(new int(1))
    {
        data = unique_ptr.get();
        unique_ptr.release();
    }

    ~shared_ptr()
    {
        release();
    }

    shared_ptr(const shared_ptr& copy) : data(copy.data), count(copy.count)
    {
        if (count != nullptr)
        {
            ++(*count);
        }
    }

    shared_ptr& operator=(const shared_ptr& copy)
    {
        if (this != &copy)
        {
            data = copy.data;
            count = copy.count;
            if (count != nullptr)
            {
                ++(*count);
            }
        }
        return *this;
    }

    shared_ptr& operator=(unique_ptr<T>&& unique_ptr)
    {
        release();
        data = unique_ptr.get();
        unique_ptr.release();
        if (count != nullptr)
        {
            count = new int(1);
        }
        else
        {
            *count = 1;
        }
        return *this;
    }

    void release() noexcept
    {
        if (count != nullptr)
        {
            (*count)--;
            if (*count == 0)
            {
                delete data;
                delete count;
                data = nullptr;
                count = nullptr;
            }
        }
    }

    void reset()
    {
        T* tmp = release();
        delete tmp;
    }

    // Const correct access owned object
    T* operator->() const { return data; }
    T& operator*()  const { return *data; }

    // Access to smart pointer state
    T* get()                 const { return data; }
    int use_count()          const { return *count; }
    explicit operator bool() const { return data; }
};