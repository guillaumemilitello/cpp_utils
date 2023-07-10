#include <iostream>
#include <memory>
#include <string>

struct A
{
    virtual ~A() = default;

    virtual void doSomething() const = 0;
};

struct A1 : public A
{
    void doSomething() const override
    {
        std::cout << "A1: doSomething" << std::endl;
    }
};

struct NullA : public A
{
    void doSomething() const override
    {
        std::cout << "NullA: cannot doSomething" << std::endl;
    }
};

struct Factory
{
    static std::unique_ptr<A> makeA(const std::string &s_)
    {
        if ("A1" == s_)
        {
            return std::make_unique<A1>();
        }
        else // A2 does not exist, returning a NullA object
        {
            return std::make_unique<NullA>();
        }
    }
};

int main()
{
    auto a1Ptr {Factory::makeA("A1")};
    if (a1Ptr)
    {
        a1Ptr->doSomething();
        // A1: doSomething
    }

    auto a2Ptr {Factory::makeA("A2")};
    if (a2Ptr)
    {
        a2Ptr->doSomething();
        // NullA: cannot doSomething
        // check return, handle in a different path
    }

    return 0;
}