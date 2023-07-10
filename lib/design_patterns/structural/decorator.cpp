#include <iostream>
#include <memory>


// The base component interface defines operations that can be altered by decorators
struct A
{
    virtual ~A() = default;

    virtual void doSomething() const = 0;
};

struct A1 : A
{
    void doSomething() const override
    {
        std::cout << "A1: doSomething\n";
    }
};

// The base Decorator class follows the same interface as the other components.
struct DecoratorA : A
{
    DecoratorA(const std::shared_ptr<A>& aPtr_) : _aPtr(aPtr_) {}

    void doSomething() const override
    {
        _aPtr->doSomething();
    }

private:
    std::shared_ptr<A> _aPtr;
};

struct DecoratorA1 : DecoratorA
{
    DecoratorA1(const std::shared_ptr<A>& aPtr_) : DecoratorA(aPtr_) {}

    // Decorators delegate all work to the wrapped component
    void doSomething() const override
    {
        std::cout << "DecoratorA1: doSomething\n";
        DecoratorA::doSomething();
    }
};

struct DecoratorA2 : DecoratorA
{
    DecoratorA2(const std::shared_ptr<A>& aPtr_) : DecoratorA(aPtr_) {}

    void doSomething() const override
    {
        //  Decorators can execute their behavior either before or after the call to a wrapped object.
        std::cout << "DecoratorA2: doSomething\n";
        DecoratorA::doSomething();
    }
};

int main()
{
    auto a1Ptr {std::make_shared<A1>()};
    a1Ptr->doSomething();
    // A1: doSomething

    // The client code works with all objects using the A interface
    DecoratorA1 decoratorA1 {a1Ptr};
    decoratorA1.doSomething();
    // DecoratorA1: doSomething
    // A1: doSomething

    DecoratorA2 decoratorA2 {a1Ptr};
    decoratorA2.doSomething();
    // DecoratorA2: doSomething
    // A1: doSomething

    return 0;
}