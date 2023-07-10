#include <iostream>

template<typename T>
class CtorWrapper
{
    T _value = 0;

public:
    CtorWrapper()
    {
        std::cout << "default ctor\n";
    }

    CtorWrapper(T value_) : _value(value_)
    {
        std::cout << "value ctor " << _value << "\n";
    }

    CtorWrapper(const CtorWrapper& rhs_) : _value(rhs_._value)
    {
        std::cout << "copy ctor " << _value << "\n";
    }

    CtorWrapper &operator=(const CtorWrapper& rhs_)
    {
        _value = rhs_._value;
        std::cout << "copy oper " << _value << "\n";
        return *this;
    }

    CtorWrapper(CtorWrapper&& rhs_) : _value(std::move(rhs_._value))
    {
        std::cout << "move ctor " << _value << "\n";
    }

    CtorWrapper &operator=(CtorWrapper&& rhs_)
    {
        _value = std::move(rhs_._value);
        std::cout << "move oper " << _value << "\n";
        return *this;
    }

    ~CtorWrapper()
    {
        std::cout << "dtor " << _value << "\n";
    }

    friend std::ostream& operator<<(std::ostream &os, const CtorWrapper& ctorWrapper_)
    {
        os << ctorWrapper_._value;
        return os;
    }
};
