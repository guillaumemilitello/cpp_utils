#include <new> // std::nothrow

template <typename T>
class unique_ptr
{
    T* data;

public:
    unique_ptr() : data(nullptr) {}

    explicit unique_ptr(T* data) : data(data) {}

    ~unique_ptr() { delete data; }

    // Constructor/Assignment that binds to nullptr
    // This makes usage with nullptr cleaner
    unique_ptr(std::nullptr_t) : data(nullptr) {}

    unique_ptr& operator=(std::nullptr_t)
    {
        reset();
        return *this;
    }

    // Constructor/Assignment that allows move semantics
    unique_ptr(unique_ptr&& moving) noexcept
    {
        moving.swap(*this);
    }

    unique_ptr& operator=(unique_ptr&& moving) noexcept
    {
        moving.swap(*this);
        return *this;
    }

    // Constructor/Assignment for use with types derived from T
    template <typename U>
    unique_ptr(unique_ptr<U>&& moving)
    {
        unique_ptr<T> tmp(moving.release());
        tmp.swap(*this);
    }

    template <typename U>
    unique_ptr& operator=(unique_ptr<U>&& moving)
    {
        unique_ptr<T> tmp(moving.release());
        tmp.swap(*this);
        return *this;
    }

    // Remove compiler generated copy semantics
    unique_ptr(unique_ptr const &) = delete;
    unique_ptr& operator=(unique_ptr const &) = delete;

    // Const correct access owned object
    T* operator->() const { return data; }
    T &operator*() const { return *data; }

    // Access to smart pointer state
    T* get() const { return data; }
    explicit operator bool() const { return data; }

    // Modify object state
    T* release() noexcept
    {
        T* result = nullptr;
        std::swap(result, data);
        return result;
    }

    void swap(unique_ptr& src) noexcept
    {
        std::swap(data, src.data);
    }

    void reset()
    {
        T* tmp = release();
        delete tmp;
    }
};
