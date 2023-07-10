#pragma once

include <new> // std::nothrow

template<typename T>
class shared_ptr
{
    T*   data;
    int* count;

public:
    shared_ptr() : data(nullptr), count(nullptr) {}

    // Explicit constructor
    explicit shared_ptr(T* data) : data(data), count(new (std::nothrow) int(1)) // use the no throw version of new
    {
        // Check if the pointer correctly allocated
        if (count == nullptr)
        {
            // If we failed then delete the pointer
            // and manually throw the exception
            delete data;
            throw std::bad_alloc();
        }
    }

    ~shared_ptr()
    {
        --(*count);
        if (*count == 0)
        {
            delete data;
        }
    }

    shared_ptr(const shared_ptr& copy) : data(copy.data), count(copy.count)
    {
        ++(*count);
    }

    // Use the copy and swap idiom
    // It works perfectly for this situation
    shared_ptr& operator=(shared_ptr rhs)
    {
        rhs.swap(*this);
        return *this;
    }

    shared_ptr& operator=(T* newData)
    {
        shared_ptr tmp(newData);
        tmp.swap(*this);
        return *this;
    }

    // Constructor/Assignment that allows move semantics
    shared_ptr(shared_ptr&& moving) noexcept
    {
        moving.swap(*this);
    }

    shared_ptr& operator=(shared_ptr&& moving) noexcept
    {
        moving.swap(*this);
        return *this;
    }

    // Always good to have a swap function
    // Make sure it is noexcept
    void swap(shared_ptr& src) noexcept
    {
        std::swap(data,  src.data);
        std::swap(count, src.count);
    }

    // Modify object state
    T* release() noexcept
    {
        shared_ptr result;
        result.swap(*this);
        return result;
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
    explicit operator bool() const { return data; }
};