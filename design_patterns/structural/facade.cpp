#include <iostream>

 // The system can accept requests either from the facade or client directly
struct A1
{
    void doSomething1() const
    {
        std::cout << "A1: doSomething1\n";
    }

    void doSomething2() const
    {
        std::cout << "A1: doSomething2\n";
    }
};

struct A2
{
    void doSomething1() const
    {
        std::cout << "A2: doSomething1\n";
    }

    void doSomething2() const
    {
        std::cout << "A2: doSomething2\n";
    }
};

// A facade delegates the client requests to the appropriate objects within the subsystems
struct Facade
{
    Facade() : _a1(A1{}), _a2(A2{}) {} // need to initialize const members

    // A facade does not expose the same interface as the subsystems, it is a simplifier one
    void doSomething() const
    {
        _a1.doSomething1();
        _a2.doSomething1();
        _a1.doSomething2();
        _a2.doSomething2();
    }

private:
    const A1 _a1;
    const A2 _a2;
};

int main()
{
    Facade facade;
    facade.doSomething();
    // A1: doSomething1
    // A2: doSomething1
    // A1: doSomething2
    // A2: doSomething2

    return 0;
}