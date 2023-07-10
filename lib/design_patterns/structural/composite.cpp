#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <list>
#include <string>

// The base class declares common operations for both simple and complex objects of a composition
// The base class can define the child-management, parent-management
struct A
{
    virtual ~A(){}

    void setParent(const std::shared_ptr<A>& parentPtr_)
    {
        _parentPtr = parentPtr_;
    }

    virtual void add(const std::shared_ptr<A>& aPtr_) {}
    virtual void remove(const std::shared_ptr<A>& aPtr_) {}

    // You can provide a method that lets the client code figure out whether a component has children
    virtual bool isComposite() const
    {
        return false;
    }

    virtual std::string doSomething() const = 0;

private:
    std::shared_ptr<A> _parentPtr;
};

// The leaf class represents the end objects of a composition. A leaf can't have any children
struct LeafA : A
{
    explicit LeafA(unsigned number_) : _number(number_) {}

    // Usually the leaf objects do the actual work delegated from composite parents
    std::string doSomething() const override
    {
        return "LeafA " + std::to_string(_number) + ": doSomething\n";
    }

private:
    unsigned _number;
};

// The composite class represents the complex components that may have children
struct CompositeA : A, std::enable_shared_from_this<CompositeA>
{
    explicit CompositeA(unsigned number_) : _number(number_) {}

    void add(const std::shared_ptr<A> &aPtr_) override
    {
        _childrenPtr.emplace_back(aPtr_);
        aPtr_->setParent(shared_from_this());
    }

    void remove(const std::shared_ptr<A> &aPtr_) override
    {
        _childrenPtr.remove(aPtr_);
        aPtr_->setParent(nullptr);
    }

    bool isComposite() const override
    {
        return true;
    }

    // Usually the composite objects delegate the actual work to their children and aggregate the result
    std::string doSomething() const override
    {
        std::string result;
        for (const auto& cPtr : _childrenPtr)
        {
            result += cPtr->doSomething();
        }
        return "CompositeA " + std::to_string(_number) + ":\n" + result;
    }

private:
    std::list<std::shared_ptr<A>> _childrenPtr;
    unsigned _number;
};

int main()
{
    auto leaf1Ptr {std::make_shared<LeafA>(1)};

    std::cout << leaf1Ptr->doSomething();
    // LeafA 1: doSomething

    auto branch1Ptr {std::make_shared<CompositeA>(1)};
    auto leaf2Ptr {std::make_shared<LeafA>(2)};
    branch1Ptr->add(leaf1Ptr);
    branch1Ptr->add(leaf2Ptr);

    auto branch2Ptr {std::make_shared<CompositeA>(2)};
    auto leaf3Ptr {std::make_shared<LeafA>(3)};
    branch2Ptr->add(leaf3Ptr);

    auto treePtr {std::make_shared<CompositeA>(0)};
    treePtr->add(branch1Ptr);
    treePtr->add(branch2Ptr);

    std::cout << treePtr->doSomething();
    // CompositeA 0:
    // CompositeA 1:
    // LeafA 1: doSomething
    // LeafA 2: doSomething
    // CompositeA 2:
    // LeafA 3: doSomething

    branch1Ptr->remove(leaf1Ptr);
    std::cout << treePtr->doSomething();
    // CompositeA 0:
    // CompositeA 1:
    // LeafA 2: doSomething
    // CompositeA 2:
    // LeafA 3: doSomething

    return 0;
}