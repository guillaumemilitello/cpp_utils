#pragma once

#include <iostream>

template<typename T>
struct QueueList
{
public:
    ~QueueList()
    {
        Elem* e = _back;
        while(e != nullptr)
        {
            Elem* ed = e;
            e = e->next;
            delete ed;
        }
    }

    const T& back() const
    {
        return _back->data;
    }

    const T& front() const
    {
        return _front->data;
    }

    void push_back(const T& data_)
    {
        Elem* e = new Elem();
        e->data = data_;

        Elem* eb = _back;
        if (eb != nullptr)
        {
            _back->prev = e;
            e->next = _back;
        }
        else
        {
            _front = e;
        }

        _back = e;
    }

    void pop_front()
    {
        Elem* ef = _front;
        _front = ef->prev;
        _front->next = nullptr;
        delete ef;
    }

    template<typename T_>
    friend std::ostream& operator<<(std::ostream& os, const QueueList<T_>& q);

private:
    struct Elem
    {
        Elem* prev = nullptr;
        Elem* next = nullptr;
        T data;
    };

    Elem*  _front = nullptr;
    Elem*  _back = nullptr;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const QueueList<T>& q)
{
    os << "[ ";
    typename QueueList<T>::Elem* e = q._front;
    while(e != nullptr)
    {
        os << e->data << " ";
        e = e->prev;
    }
    os << "]";
    return os;
}

template<typename T, size_t Size>
struct QueueArray
{
public:
    const T& back() const { return _array[_back]; }
    const T& front() const { return _array[_front]; }

    void push_back(const T& data_)
    {
        _array[_back] = data_;
        setToNext(_back);
    }

    void pop_front()
    {
        setToNext(_front);
    }

    template<typename T_, size_t Size_>
    friend std::ostream& operator<<(std::ostream& os, const QueueArray<T_, Size_>& q);

private:
    static void setToNext(size_t& i_) { i_ = (i_ + 1) % Size;}

    std::array<T, Size+1> _array;
    size_t _front = 0;
    size_t _back = 0;
};

template<typename T, size_t Size>
std::ostream& operator<<(std::ostream& os, const QueueArray<T, Size>& q)
{
    os << "[ ";
    size_t i = q._front;
    while (i != q._back)
    {
        os << q._array[i] << " ";
        QueueArray<T, Size>::setToNext(i);
    }
    os << "]";
    return os;
}
