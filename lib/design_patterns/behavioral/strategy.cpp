#include <iostream>
#include <memory>

// The Strategy interface declares operations common to all supported algorithm versions
// The Context uses this interface to call the algorithm defined by concrete strategies
struct Strategy
{
    virtual ~Strategy() = default;
    virtual void doSomething() const = 0;
};

// The Context maintains a reference to one of the Strategy objects
// The Context does not know the concrete class of a strategy
struct Context
{
    Context(std::shared_ptr<Strategy> strategyPtr_) : _strategyPtr(strategyPtr_) {}

    void setStrategy(std::shared_ptr<Strategy> strategyPtr_)
    {
        _strategyPtr = strategyPtr_;
    }

    void doSomething() const
    {
        if (_strategyPtr)
        {
            _strategyPtr->doSomething();
        }
    }

private:
    std::shared_ptr<Strategy> _strategyPtr;
};


struct StrategyA : public Strategy
{
    void doSomething() const override
    {
        std::cout << "StrategyA: doSomething\n";
    }
};

struct StrategyB : public Strategy
{
    void doSomething() const override
    {
        std::cout << "StrategyB: doSomething\n";
    }
};

int main()
{
    auto strategyAPtr {std::make_shared<StrategyA>()};
    auto strategyBPtr {std::make_shared<StrategyB>()};
    // only one reference of the context
    // the strategy objects do not hold a reference of the context
    Context context {strategyAPtr};
    context.doSomething();
    // StrategyA: doSomething
    context.setStrategy(strategyBPtr);
    context.doSomething();
    // StrategyB: doSomething

    return 0;
}
