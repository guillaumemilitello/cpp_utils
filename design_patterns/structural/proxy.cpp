#include <iostream>

// The interface declares common operations for both the real subject and the proxy
struct A
{
    virtual void doSomething() const = 0;
};

struct RealA : public A
{
    void doSomething() const override
    {
        std::cout << "RealA: Handling request\n";
    }
};

struct ProxyA : public A
{
    ProxyA(RealA& a_) : _realA(a_) {}

    void doSomething() const override
    {
        if (needRealA())
        {
            _realA.doSomething();
        }
    }

private:
    bool needRealA() const
    {
        std::cout << "ProxyA: Checking prior requesting RealA\n";
        return true;
    }

    // The proxy maintains a reference to an object of the real subject class
    RealA& _realA;
};

int main()
{
    auto doSomethingWithA = [](const A& a_){ a_.doSomething(); };

    RealA realA;
    doSomethingWithA(realA);
    // RealA: Handling request

    ProxyA proxyA {realA};
    doSomethingWithA(proxyA);
    // ProxyA: Checking prior requesating RealA
    // RealA: Handling request

    return 0;
}
