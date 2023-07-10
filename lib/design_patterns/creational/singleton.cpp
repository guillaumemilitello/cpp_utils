#include <iostream>

class Singleton
{
public:
    // controls the access to the singleton, instantiate an instance at the first call only
    static Singleton& getInstance()
    {
        static Singleton instance;
        return instance;
    }

    // do not allow clone or assignation
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
    // deleted functions should generally be public as it results in better error messages
    // due to the compilers behavior to check accessibility before deleted status

    void doSomething()
    {
        std::cout << "Singleton: doSomething" << std::endl;
    }

private:
    Singleton() //can only be called from getInstance() with a private constructor
    {
        std::cout << "Singleton: created" << std::endl;
    }
};

int main()
{
    auto& a {Singleton::getInstance()};
    // Singleton: created

    a.doSomething();
    // Singleton: doSomething

    return 0;
}
