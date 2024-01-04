#include <stdexcept>
#include <initializer_list>

template <typename T>
class Vector
{
public:
    Vector() : _data(nullptr), _capacity(0), _size(0) {}

    Vector(std::initializer_list<T> initList) : Vector()
    {
        resize(initList.size());

        for (const T& value : initList)
        {
            _data[_size++] = std::move(value);
        }
    }

    ~Vector()
    {
        for (size_t i = 0; i < _size; ++i)
        {
            _data[i].~T();
        }
        std::free(_data);
    }

    void reserve(size_t capacity)
    {
        if (capacity  > _capacity)
        {
            resize(capacity);
        }
    }

    void emplace_back(T&& value)
    {
        if (this->size() + 1  > _capacity)
        {
            resize();
        }
        _data[_size++] = std::move(value);
    }

    T& operator[](size_t index)
    {
        if (index >= this->size())
        {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    size_t size() const
    {
        return _size;
    }

    size_t capacity() const
    {
        return _capacity;
    }

private:
    T* _data;
    size_t _capacity;
    size_t _size;

    void resize(size_t newCapacity = 0)
    {
        if (newCapacity == 0)
        {
            newCapacity = _capacity == 0 ? 1 : _capacity * 2;
        }
        T* newData = static_cast<T*>(std::malloc(newCapacity * sizeof(T)));
        for (size_t i = 0; i < _size; ++i)
        {
            new (&newData[i]) T(std::move(_data[i]));
            _data[i].~T();
        }
        std::free(_data);
        _data = newData;
        _capacity = newCapacity;
    }
};
