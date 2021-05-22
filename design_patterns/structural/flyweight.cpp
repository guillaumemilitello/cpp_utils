#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>

// Shared protion of the flyweight
struct State
{
    State(const std::string& state_) : _stateStr(state_) {}

    friend std::ostream& operator<<(std::ostream& os, const State& state_)
    {
        return os << state_._stateStr;
    }

    std::string _stateStr;
};

// The Flyweight stores a common portion of the state (intrinsic state)
// The Flyweight accepts the rest of the state (extrinsic state) unique for each entity
struct A
{
    A(const std::string& statePtr_) : _intrinsicStatePtr(std::make_shared<State>(statePtr_)) {}

    A(const A& other) : _intrinsicStatePtr(other._intrinsicStatePtr) {}

    State& state() const
    {
        return *_intrinsicStatePtr;
    }

    void doSomething() const
    {
        std::cout << "A doSomething, state="<< *_intrinsicStatePtr << std::endl;
    }
private:
    std::shared_ptr<State> _intrinsicStatePtr;
};

// The Factory is looking to return a refernce of the intrinsic state or to create a new one
struct Factory
{
    Factory(std::initializer_list<std::string> states_)
    {
        for (const std::string& s : states_)
        {
            _flyweights.emplace(s, A(s));
        }
    }

    A getFlyweight(const std::string& state_) const
    {
        if (_flyweights.find(state_) == _flyweights.end())
        {
            std::cout << "Factory: can't find a flyweight for " << state_ << ", creating new one\n";
            _flyweights.emplace(state_, A(state_));
        }
        else
        {
            std::cout << "Factory: reusing existing flyweight for " << state_ << "\n";
        }

        return _flyweights.at(state_);
    }

private:
    mutable std::unordered_map<std::string, A> _flyweights;
};

int main()
{
    Factory f {"state0", "state1"};
    A a0 {f.getFlyweight("state0")};
    // Factory: reusing existing flyweight for state0
    A a1 {f.getFlyweight("state0")};
    // Factory: reusing existing flyweight for state0
    A a2 {f.getFlyweight("state1")};
    // Factory: reusing existing flyweight for state1
    A a3 {f.getFlyweight("state2")};
    // Factory: can't find a flyweight for state2, creating new one

    State& s0 {a0.state()};
    s0._stateStr = "newState0";

    a0.doSomething();
    // A doSomething, state=newState0
    a1.doSomething();
    // A doSomething, state=newState0
    a2.doSomething();
    // A doSomething, state=state1
    a3.doSomething();
    // A doSomething, state=state2
}
