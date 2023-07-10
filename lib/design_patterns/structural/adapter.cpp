#include <iostream>

struct A
{
  virtual ~A() = default;

  virtual void doSomething() const
  {
    std::cout << "A: doSomething\n";
  }
};

//  NewA interface is incompatible and needs to be adapted before using it
struct NewA
{
  virtual ~NewA() = default;

  virtual void doSomethingNew() const
  {
    std::cout << "NewA: doSomethingNew\n";
  }
};

// Class AdapterA makes A interface compatible with NewA using multiple inheritance
struct AdapterA : A, NewA
{
  // overriding NewA method to call correct A method
  void doSomethingNew() const override
  {
    std::cout << "AdapterA: doSomethingNew\n";
    A::doSomething();
  }
};


int main()
{
    A a;
    a.doSomething();
    // A: doSomething

    NewA newA;
    newA.doSomethingNew();
    // NewA: doSomethingNew

    AdapterA adapterA;
    adapterA.doSomethingNew();
    // AdapterA: doSomethingNew
    // A: doSomething

  return 0;
}