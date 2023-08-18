#pragma once

template <typename T>
class unique_ptr
{
    T* _data;

public:
    unique_ptr() : _data(nullptr) {}

    unique_ptr(T* data_) : _data(data_) {}

    ~unique_ptr()
    {
        release();
    }

    // Constructor/Assignment that allows move semantics
    unique_ptr(unique_ptr&& move) noexcept : _data(move._data)
    {
        move._data = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& move) noexcept
    {
        if (this != &move)
        {
            delete _data;
            _data = move._data;
            move._data = nullptr;
        }
        return *this;
    }

    // Remove compiler generated copy semantics
    unique_ptr(unique_ptr const &) = delete;
    unique_ptr& operator=(unique_ptr const &) = delete;

    // Const correct access owned object
    T* operator->() const { return _data; }
    T& operator*()  const { return *_data; }

    // Access to smart pointer state
    T* get() const { return _data; }
    explicit operator bool() const { return _data; }

    T* release() noexcept
    {
        T* result = _data;
        _data = nullptr;
        return result;
    }

    void reset(T* data_ = nullptr) noexcept
    {
        delete _data;
        _data = data_;
    }
};
