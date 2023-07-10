#include <iostream>
#include <memory>


// A interface declares a method for executing a command
struct A
{
    virtual ~A() = default;
    virtual void doSomething() const = 0;
};


// Simple concrete commands can implement the operations on their own
struct A1 : public A
{
    A1(const std::string &param_) : _param(param_) {}

    void doSomething() const override
    {
        std::cout << "A1: doSomething: " << _param << "\n";
    }

private:
    std::string _param;
};

// The Receiver itself does the actual work
struct Receiver
{
    void doSomething(const std::string &param_) const
    {
        std::cout << "Receiver: doSomething: " << param_ << "\n";
    }

    void doSomethingElse(const std::string &param_) const
    {
        std::cout << "Receiver: doSomethingElse: " << param_ << "\n";
    }
};

// Most commands only handle the details of how a request is passed to the receiver
struct A2 : public A
{
    A2(Receiver receiver_, const std::string &param0_, const std::string &param1_)
        : _receiver(receiver_), _param0(param0_), _param1(param1_) {}

    void doSomething() const override
    {
        std::cout << "A2: doSomething\n";
        _receiver.doSomething(_param0);
        _receiver.doSomethingElse(_param1);
    }

private:
    const Receiver _receiver;
    std::string _param0;
    std::string _param1;
};

// The Invoker encapsulate the request and can be parameterized with one or several commands
struct Invoker
{
    Invoker(std::unique_ptr<A> onStart_, std::unique_ptr<A> onFinish_)
        : _onStart(std::move(onStart_)), _onFinish(std::move(onFinish_)) {}

    void doSomething()
    {
        if (_onStart)
        {
            _onStart->doSomething();
        }
        std::cout << "Invoker: doSomething\n";
        if (_onFinish)
        {
            _onFinish->doSomething();
        }
    }

private:
    std::unique_ptr<A> _onStart;
    std::unique_ptr<A> _onFinish;
};

int main()
{
    Invoker invoker {std::make_unique<A1>("warmup"),
                     std::make_unique<A2>(Receiver{}, "cooldown", "stretching")};
    invoker.doSomething();
    // A1: doSomething: warmup
    // Invoker: doSomething
    // A2: doSomething
    // Receiver: doSomething: cooldown
    // Receiver: doSomethingElse: stretching

    return 0;
}
