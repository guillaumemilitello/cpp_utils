#include <iostream>
#include <vector>
#include <string>
#include <memory>

struct BuilderA;

// A will list its parts
struct A
{
    void listParts() const
    {
        std::string out {"A parts: "};
        for (const auto& part : _partVect)
        {
            out += part + ",";
        }
        out.pop_back();
        std::cout << out << "\n";
    }

    static std::unique_ptr<BuilderA> build(std::string&& rootName)
    {
        return std::make_unique<BuilderA>(std::forward<std::string>(rootName));
    }

private:
    std::vector<std::string> _partVect;

    friend class BuilderA;
};

struct BuilderA
{
    BuilderA(const std::string& rootName) : _rootName(rootName) {}

    BuilderA* build1()
    {
        _a._partVect.emplace_back("Part" + _rootName + "A1");
        return this;
    }

    BuilderA* build2()
    {
        _a._partVect.emplace_back("Part" + _rootName + "A2");
        return this;
    }

    A getA() const
    {
        return _a;
    }

private:
    A _a; // All production steps work with the same instance
    const std::string _rootName;
};

int main()
{
    auto builderATest {A::build("Test")};
    builderATest->build1();
    builderATest->getA().listParts();
    // A parts: PartTestA1

    auto builderAExample {A::build("Example")};
    builderAExample->build1()->build2();
    builderAExample->getA().listParts();
    // A parts: PartExampleA1, PartExampleA2
}