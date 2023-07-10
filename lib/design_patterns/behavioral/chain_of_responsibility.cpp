#include <iostream>
#include <string>
#include <memory>

struct Handler
{
    virtual const std::shared_ptr<Handler>& setNext(const std::shared_ptr<Handler>& handlerPtr_) = 0;
    virtual void doSomething(const std::string& request_) const = 0;
};

struct A : Handler
{
    const std::shared_ptr<Handler>& setNext(const std::shared_ptr<Handler>& handlerPtr_) override
    {
        _nextHandlerPtr = handlerPtr_;
        // Returning a handler from here will let us link handlers in a convenient way like to create a chain in the code
        // ptr->setNext(...)->setNext(...);
        return handlerPtr_;
    }

    void doSomething(const std::string& request_) const override
    {
        if (_nextHandlerPtr)
        {
            return _nextHandlerPtr->doSomething(request_);
        }
    }

private:
    std::shared_ptr<Handler> _nextHandlerPtr;
};

struct A1 : A
{
    // A concrete handler either handles a request or pass it to the next handler in the chain
    void doSomething(const std::string& request_) const override
    {
        std::cout << "A1: doSomething\n";
        if (request_ == "ForA1")
        {
            std::cout << "ForA1: doSomething\n";
        }
        else
        {
            A::doSomething(request_);
        }
    }
};

struct A2 : A
{
    void doSomething(const std::string& request_) const override
    {
        std::cout << "A2: doSomething\n";
        if (request_ == "ForA2")
        {
            std::cout << "ForA2: doSomething\n";
        }
        else
        {
            A::doSomething(request_);
        }
    }
};

struct A3 : A
{
    void doSomething(const std::string& request_) const override
    {
        std::cout << "A3: doSomething\n";
        if (request_ == "ForA3")
        {
            std::cout << "ForA3: doSomething\n";
        }
        else
        {
            A::doSomething(request_);
        }
    }
};

int main()
{
    const auto a1 {std::make_shared<A1>()};
    const auto a2 {std::make_shared<A2>()};
    const auto a3 {std::make_shared<A3>()};
    a1->setNext(a2)->setNext(a3);

    a1->doSomething("ForA3");
    // A1: doSomething
    // A2: doSomething
    // A3: doSomething
    // ForA3: doSomething

    a2->doSomething("ForA3");
    // A2: doSomething
    // A3: doSomething
    // ForA3: doSomething

    return 0;
}
