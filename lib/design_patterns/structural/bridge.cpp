#include <iostream>
#include <memory>

// Impl defines a common interface for Abstraction
struct Impl
{
    using Ptr = std::unique_ptr<Impl>;
    virtual ~Impl() = default;
    virtual void doSomething() const = 0;
};

// Concrete Impl could correspond to a specific platform or API version
struct Impl1 : Impl
{
    void doSomething() const override
    {
        std::cout << "Impl1: doSomething\n";
    }
};

struct Impl2 : Impl
{
    void doSomething() const override
    {
        std::cout << "Impl2: doSomething\n";
    }
};

// Abstraction defines the interface for the client code
// It maintains a reference to an object of Impl and delegates all of the real work
struct Abstraction
{
    explicit Abstraction(const Impl& impl_) : _impl(impl_) {}

    void doSomething() const
    {
        _impl.doSomething();
    }

private:
    const Impl& _impl;
};

int main()
{
    Impl1 impl1;
    Abstraction abstraction1(impl1);

    Impl2 impl2;
    Abstraction abstraction2(impl2);

    abstraction1.doSomething();
    // Impl1: doSomething

    abstraction2.doSomething();
    // Impl2: doSomething

    return 0;
}
