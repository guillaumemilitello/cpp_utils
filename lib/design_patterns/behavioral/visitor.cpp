#include <iostream>
#include <vector>
#include <memory>

struct A1;
struct A2;

// The Visitor interface declares a set of visiting methods that correspond to the exact class of the component
struct Visitor
{
    virtual ~Visitor() = default;

    virtual void visitA1(const std::shared_ptr<const A1>& a1Ptr_) const = 0;
    virtual void visitA2(const std::shared_ptr<const A2>& a2Ptr_) const = 0;
};

// The base interface declares an `accept` method with the Visitor
struct A
{
    virtual ~A() = default;

    virtual void accept(const std::shared_ptr<Visitor>& visitorPtr_) const = 0;
};

struct A1 : A, std::enable_shared_from_this<A1>
{
    void accept(const std::shared_ptr<Visitor>& visitorPtr_) const override
    {
        std::cout << "A1: accept\n";
        visitorPtr_->visitA1(shared_from_this());
    }

    void doSomething() const
    {
        std::cout << "A1: doSomething\n";
    }
};

struct A2 : A, std::enable_shared_from_this<A2>
{
    void accept(const std::shared_ptr<Visitor>& visitorPtr_) const override
    {
        std::cout << "A2: accept\n";
        visitorPtr_->visitA2(shared_from_this());
    }

    void doSomething() const
    {
        std::cout << "A2: doSomething\n";
    }

    void doSomethingElse() const
    {
        std::cout << "A2: doSomethingElse\n";
    }
};

// The visitor class holds the operational logic away from the objects, adding operations without changing the structure
struct Visitor1 : Visitor
{
    void visitA1(const std::shared_ptr<const A1>& a1Ptr_) const override
    {
        a1Ptr_->doSomething();
    }

    void visitA2(const std::shared_ptr<const A2>& a2Ptr_) const override
    {
        a2Ptr_->doSomething();
        a2Ptr_->doSomethingElse();
    }
};

int main()
{
    const std::vector<std::shared_ptr<A>> aPtrVect{std::make_shared<A1>(), std::make_shared<A2>()};
    const auto visitorPtr{std::make_shared<Visitor1>()};
    for (const auto &aPtr : aPtrVect)
    {
        // run visitor operations over any set of elements without figuring out their concrete classes
        aPtr->accept(visitorPtr);
        // A1: accept
        // A1: doSomething

        // A2: accept
        // A2: doSomething
        // A2: doSomethingElse
    }

    return 0;
}
