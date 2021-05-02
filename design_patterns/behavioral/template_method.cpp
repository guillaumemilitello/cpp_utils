#include <iostream>

// The template method defines the skeleton of an algorithm
struct A
{
    void doSomething() const
    {
        doSomething1();
        doSomething2();
        doSomething3();
    }

protected:
    void doSomething1() const
    {
        std::cout << "A: doSomething1\n";
    }

    virtual void doSomething2() const = 0;

    virtual void doSomething3() const {}
};

// Usually, concrete classes override only a fraction of base class' operations
struct A1 : A
{
protected:
    void doSomething2() const override
    {
        std::cout << "A1: doSomething2\n";
    }
};

struct A2 : A
{
protected:
    void doSomething2() const override
    {
        std::cout << "A2: doSomething2\n";
    }

    void doSomething3() const override
    {
        std::cout << "A2: doSomething3\n";
    }
};

int main()
{
    // The template method works at the class level, so it’s static
    // We need a new instance to change the algorithm

    A1 a1;
    a1.doSomething();
    // A: doSomething1
    // A1: doSomething2

    A2 a2;
    a2.doSomething();
    // A: doSomething1
    // A2: doSomething2
    // A2: doSomething3

    return 0;
}