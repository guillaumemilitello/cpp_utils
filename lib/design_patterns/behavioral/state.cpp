#include <iostream>
#include <memory>

struct Context;

// The State interface provides a backreference to the Context object, associated with the State
// This backreference can be used by States to transition the Context to another State
struct State
{
    virtual ~State() = default;

    virtual std::string name() const = 0;
    virtual void doSomething1() = 0;
    virtual void doSomething2() = 0;

    void setContext(std::shared_ptr<Context>&& contextPtr_)
    {
        _contextPtr = contextPtr_;
    }

    std::shared_ptr<Context> _contextPtr;
};

// The Context maintains a reference to an instance of the current state
struct Context : std::enable_shared_from_this<Context>
{
    // The Context allows changing state at runtime, update the State object
    void transitionTo(std::unique_ptr<State>&& state_)
    {
        std::cout << "Context: transition to " << state_->name() << "\n";
        _state = std::move(state_);
        _state->setContext(shared_from_this());
    }

    // The Context delegates part of its behavior to the current State object
    void doSomething1()
    {
        if (_state)
        {
            _state->doSomething1();
        }
    }
    void doSomething2()
    {
        if (_state)
        {
            _state->doSomething2();
        }
    }

private:
    std::unique_ptr<State> _state;
};

struct StateA : State
{
    std::string name() const override
    {
        return "StateA";
    }

    void doSomething1() override;

    void doSomething2() override
    {
        std::cout << "StateA: doSomething2\n";
    }
};

struct StateB : State
{
    std::string name() const override
    {
        return "StateB";
    }

    void doSomething1() override
    {
        std::cout << "StateB: doSomething1\n";
    }
    void doSomething2() override
    {
        std::cout << "StateB: doSomething2\n";

        std::cout << "StateB: wants to change the state of the context\n";
        _contextPtr->transitionTo(std::make_unique<StateA>());
    }
};

void StateA::doSomething1()
{
    std::cout << "StateA: doSomething1\n";

    std::cout << "StateA: wants to change the state of the context\n";
    _contextPtr->transitionTo(std::make_unique<StateB>());
}

int main()
{
    auto context {std::make_shared<Context>()};
    context->transitionTo(std::make_unique<StateA>());
    // initial state cannot get the context with shared_from_this() vs. raw pointer from ctor
    // Context: transition to StateA
    context->doSomething1();
    // StateA: handles doSomething1
    // StateA: wants to change the state of the context
    // Context: transition to StateB
    context->doSomething2();
    // StateB: handles doSomething2
    // StateB: wants to change the state of the context
    // Context: transition to StateA

    return 0;
}
