#include <iostream>
#include <memory>
#include <string>

struct A
{
    explicit A(const std::string& name_) : _name(name_) {}
    virtual ~A() = default;

    // add cloning ability between the same type, performs a deep copy
    virtual std::shared_ptr<A> clone() const = 0;
    virtual void doSomething() const = 0;

    void updateName(const std::string& name_)
    {
        _name = name_;
    }

protected:
    std::string _name;
};

struct A1 : A
{
    explicit A1(const std::string& name_, int number_) : A(name_), _number(number_) {}

    std::shared_ptr<A> clone() const override
    {
        return std::make_shared<A1>(*this);
    }

    void doSomething() const override
    {
        std::cout << "A1: doSomething " << _name << " " << _number << "\n";
    }

private:
    int _number;
};

struct A2 : A
{
    explicit A2(const std::string& name_, float number_) : A(name_), _number(number_) {}

    std::shared_ptr<A> clone() const override
    {
        return std::make_shared<A2>(*this);
    }

    void doSomething() const override
    {
        std::cout << "A2: doSomething " << _name << " " << _number << "\n";
    }

private:
    float _number;
};

int main()
{
    A1 a1("A1", 1);
    A2 a2("A2", 3.5);
    a1.doSomething();
    a2.doSomething();
    // A1: doSomething A1 1
    // A2: doSomething A2 3.5

    std::shared_ptr<A> a1Ptr {a1.clone()};
    std::shared_ptr<A> a2Ptr {a2.clone()};
    a1Ptr->updateName("A1C"); // working on base class after a clone
    a2Ptr->updateName("A2C");
    a1Ptr->doSomething();
    a2Ptr->doSomething();
    // A1: doSomething A1C 1
    // A2: doSomething A2C 3.5

    return 0;
}