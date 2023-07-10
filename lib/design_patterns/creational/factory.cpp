#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

struct A
{
    virtual ~A() = default;

    virtual void doSomething() const = 0;
};

// The AFactory should be able to return any kind of A
struct AFactory
{
    // the function could take variadic arguments to forward them to the make method
    static std::unique_ptr<A> make(const std::string& name_)
    {
        auto& map {getMap()};
        auto itr {map.find(name_)};
        if (itr != map.end())
        {
            return itr->second(); // calling the make method
        }
        return nullptr; // A NullA could be return
    }

    template<class T>
    static void add()
    {
        auto& map {getMap()};
        map[T::name()] = T::make;
    }

    template<class T>
    struct Register // creates an instance to register the derived classes
    {               // the best place to create it is in the cpp of the class in the unamed namespace
        Register()
        {
            add<T>();
        }
    };

private:
    // creates and refer to a unique instance of the map storing all make methods
    static std::unordered_map<std::string, std::function<std::unique_ptr<A>()>>& getMap()
    {
        static std::unordered_map<std::string, std::function<std::unique_ptr<A>()>> map;
        return map;
    }
};

struct A1 : public A
{
    static std::string name()
    {
        return "A1";
    }

    static std::unique_ptr<A> make()
    {
        return std::make_unique<A1>();
    }

    void doSomething() const override
    {
        std::cout << name() << ": doSomething" << std::endl;
    }
};
AFactory::Register<A1> A1Register;

struct A2 : public A
{
    static std::string name()
    {
        return "A2";
    }

    static std::unique_ptr<A> make()
    {
        return std::make_unique<A2>();
    }

    void doSomething() const override
    {
        std::cout << name() << ": doSomething" << std::endl;
    }
};
AFactory::Register<A2> A2Register;

int main()
{
    auto a1Ptr {AFactory::make("A1")};
    if (a1Ptr)
    {
        a1Ptr->doSomething();
        // A1: doSomething
    }

    auto a2Ptr {AFactory::make("A2")};
    if (a2Ptr)
    {
        a2Ptr->doSomething();
        // A2: doSomething
    }

    return 0;
}