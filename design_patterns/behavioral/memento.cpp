#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <chrono>
#include <memory>
#include <iomanip>
#include <string>

template<size_t Size>
std::string generate_random_string()
{
    constexpr char alphanum[] = "0123456789"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz";
    constexpr int stringLength {sizeof(alphanum) - 1};

    std::string result;
    for (size_t i = 0; i < Size; i++)
    {
        result += alphanum[std::rand() % stringLength];
    }
    return result;
}

std::string now()
{
    using namespace std::chrono;

    const auto t {system_clock::now()};
    const auto now_c {system_clock::to_time_t(t)};
    const auto delta_us {duration_cast<microseconds>(t - system_clock::from_time_t(now_c)).count()};

    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%T") << "." << std::fixed << std::setw(6) << std::setfill('0') << delta_us;
    return ss.str();
}

// Use an interface to use multiple version of the Memento class
struct Memento
{
    Memento(const std::string& state_) : _state(state_), _timeStamp(now()) {}

    std::string getState() const
    {
        return _state;
    }

    std::string getDescription() const
    {
        return _timeStamp + " [" + _state + "]";
    }

private:
    std::string _state;
    std::string _timeStamp;
};

struct A
{
    explicit A(const std::string &state_) : _state(state_) {}

    void doSomething()
    {
        std::cout << "A: doSomething\n";
        _state = generate_random_string<5>();
    }

    std::shared_ptr<Memento> save() const
    {
        std::cout << "A: saving state [" << _state << "]\n";
        return std::make_shared<Memento>(_state);
    }

    void restore(const std::shared_ptr<Memento> &memento_)
    {
        _state = memento_->getState();
        std::cout << "A: restoring state [" << _state << "]\n";
    }

private:
    std::string _state;
};


// The Caretaker does not depend on a Memento version
// Performa action on different versions of A
struct Caretaker
{
    explicit Caretaker(A &a_) : _a(a_)
    {
        backup();
    }

    void backup()
    {
        std::cout << "Caretaker: backup\n";
        _mementoPtrs.emplace_back(_a.save());
    }

    void undo()
    {
        if (_mementoPtrs.empty())
        {
            return;
        }

        _a.restore(_mementoPtrs.back());
        _mementoPtrs.pop_back();
    }

    void showHistory() const
    {
        for (auto i = _mementoPtrs.rbegin(); i != _mementoPtrs.rend(); ++i)
        {
            const auto memento {*i};
            std::cout << memento->getDescription() << "\n";
        }
    }

    A& _a;
    std::vector<std::shared_ptr<Memento>> _mementoPtrs;
};

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    A a {generate_random_string<5>()};
    Caretaker caretaker {a};
    // Caretaker: backup
    // A: saving state [UHtlm]
    a.doSomething();
    // A: doSomething
    caretaker.backup();
    // Caretaker: backup
    // A: saving state [0e9wp]
    a.doSomething();
    // A: doSomething
    caretaker.backup();
    // Caretaker: backup
    // A: saving state [XeqRh]
    a.doSomething();
    // A: doSomething
    caretaker.backup();
    // Caretaker: backup
    // A: saving state [ZdFnl]
    a.doSomething();
    // A: doSomething
    caretaker.showHistory();
    // 12:46:01.817511 [ZdFnl]
    // 12:46:01.817460 [XeqRh]
    // 12:46:01.817408 [0e9wp]
    // 12:46:01.817315 [UHtlm]
    caretaker.undo();
    // A: restoring state [ZdFnl]
    caretaker.undo();
    // A: restoring state [XeqRh]

    return 0;
}