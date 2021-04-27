#include <iostream>
#include <memory>

struct A
{
    virtual ~A(){};
    virtual void doSomething() const = 0;
};

struct A1 : public A
{
    void doSomething() const override
    {
        std::cout << "A1: doSomething\n";
    }
};

struct A2 : public A
{
    void doSomething() const override
    {
        std::cout << "A2: doSomething\n";
    }
};

struct B
{
    virtual ~B(){};
    virtual void doSomething() const = 0;
    virtual void doAnotherThing(const A& collaborator) const = 0;
};

struct B1 : public B
{
    void doSomething() const override
    {
        std::cout << "B1: doSomething\n";
    }

    void doAnotherThing(const A& collaborator) const override
    {
        std::cout << "B1: doAnotherThing\n";
        collaborator.doSomething();
    }
};

struct B2 : public B
{
    void doSomething() const override
    {
        std::cout << "B2: doSomething\n";
    }

    void doAnotherThing(const A& collaborator) const override
    {
        std::cout << "B2: doAnotherThing\n";
        collaborator.doSomething();
    }
};

// The abstract factory defines methods to create all related products
struct Factory
{
    virtual std::unique_ptr<A> makeA() const = 0;
    virtual std::unique_ptr<B> makeB() const = 0;
};

// Each concreate factory corresponds to one family product
struct Factory1 : public Factory
{
    std::unique_ptr<A> makeA() const override
    {
        return std::make_unique<A1>();
    }

    std::unique_ptr<B> makeB() const override
    {
        return std::make_unique<B1>();
    }
};

struct Factory2 : public Factory
{
    std::unique_ptr<A> makeA() const override
    {
        return std::make_unique<A2>();
    }

    std::unique_ptr<B> makeB() const override
    {
        return std::make_unique<B2>();
    }
};

int main()
{
    // client code can be called with any kind of factory
    auto useFactory = [](Factory&& factory_)
    {
        auto aPtr {factory_.makeA()};
        auto bPtr {factory_.makeB()};
        if (aPtr && bPtr)
        {
            aPtr->doSomething();
            bPtr->doAnotherThing(*aPtr);
            bPtr->doSomething();
        }
    };

    useFactory(Factory1{});
    // A1: doSomething
    // B1: doAnotherThing
    // A1: doSomething
    // B1: doSomething

    useFactory(Factory2{});
    // A2: doSomething
    // B2: doSomething
    // B2: doAnotherThing
    // A2: doSomething

    return 0;
}