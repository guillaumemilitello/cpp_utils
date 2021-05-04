#include <iostream>
#include <string>
#include <vector>

// Iterator implements the bare minimum for work with for range loops
template <typename U>
struct Iterator
{
    Iterator(U* aPtr_, size_t idx_) : _aPtr(aPtr_), _idx(idx_) {}

    void operator++()
    {
        ++_idx;
    }

    typename U::data_type& operator*()
    {
        return _aPtr->at(_idx);
    }

    bool operator==(const Iterator<U> &other_) const
    {
        return _idx == other_._idx;
    }

    bool operator!=(const Iterator<U> &other_) const
    {
        return _idx != other_._idx;
    }

private:
    U* _aPtr;
    size_t _idx;
};

// A is a generic container that provides methods for retrieving iterator instances
template <class T, unsigned Size>
struct A
{
    using data_type = T;

    explicit A(std::initializer_list<T> il_) : _topIdx(0)
    {
        for (const auto &i : il_)
        {
            _data[_topIdx++] = i;
        }
    }

    T& at(size_t i_)
    {
        return _data[i_];
    }

    Iterator<A> begin()
    {
        return Iterator<A>(this, 0);
    }

    Iterator<A> end()
    {
        return Iterator<A>(this, _topIdx);
    }

private:
    T _data[Size];
    size_t _topIdx;
};

int main()
{
    A<float, 10> a({0.5, 4.2, 1.5, 2.4});

    for (const auto& i : a)
    {
        std::cout << i << "\n";
    }

    for (Iterator<A<float, 10>> itr = a.begin(); itr != a.end(); ++itr)
    {
        std::cout << *itr << "\n";
    }

    return 0;
}