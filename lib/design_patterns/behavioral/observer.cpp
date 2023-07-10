#include <iostream>
#include <list>
#include <memory>

// Common interface for a subscription mechanism to notify multiple objects
struct IObserver
{
  virtual ~IObserver() = default;
  virtual void notify(const std::string& msg_) const = 0;
};

struct ISubject
{
  virtual ~ISubject() = default;
  virtual void attach(const std::shared_ptr<IObserver>& observer_) = 0;
  virtual void detach(const std::shared_ptr<IObserver>& observer_) = 0;
  virtual void notifyObservers(const std::string& msg_) const = 0;
};

// The Subject owns some important state and keep a list of referenced observed objects to notifies them
struct Subject : ISubject
{
  Subject(unsigned id_) : _id(id_) {}

  void attach(const std::shared_ptr<IObserver>& observer_) override
  {
    _observerPtrVect.push_back(observer_);
  }

  void detach(const std::shared_ptr<IObserver>& observer_) override
  {
    _observerPtrVect.remove(observer_);
  }

  // logic that triggers a notification
  void doSomething() const
  {
      std::cout << "Subject" << _id << ": doSomething\n";
      notifyObservers("doSomething");
  }

  void notifyObservers(const std::string& msg_) const override
  {
    for (const auto& observer : _observerPtrVect)
    {
        observer->notify(msg_);
    }
  }

 private:
  std::list<std::shared_ptr<IObserver>> _observerPtrVect;
  unsigned _id;
};

struct Observer : IObserver, std::enable_shared_from_this<Observer>
{
  Observer(unsigned id_) : _id(id_) {}

  void setSubject(const std::shared_ptr<Subject>& subjectPtr_)
  {
    if (_subjectPtr)
    {
      removeSubject();
    }

    _subjectPtr = subjectPtr_;
    _subjectPtr->attach(shared_from_this());
  }

  void removeSubject()
  {
    _subjectPtr->detach(shared_from_this());
  }

  void notify(const std::string& msg_) const
  {
    std::cout << "Observer" << _id << ": notify: " << msg_ << "\n";
  }

 private:
  std::shared_ptr<Subject> _subjectPtr;
  unsigned _id;
};

int main()
{
  auto subject1Ptr {std::make_shared<Subject>(1)};
  auto subject2Ptr {std::make_shared<Subject>(2)};
  auto observer1Ptr {std::make_shared<Observer>(1)};
  auto observer2Ptr {std::make_shared<Observer>(2)};
  auto observer3Ptr {std::make_shared<Observer>(3)};

  observer1Ptr->setSubject(subject1Ptr);
  observer2Ptr->setSubject(subject1Ptr);
  observer3Ptr->setSubject(subject1Ptr);

  subject1Ptr->doSomething();
  // Subject1: doSomething
  // Observer1: notify: doSomething
  // Observer2: notify: doSomething
  // Observer3: notify: doSomething

  subject2Ptr->doSomething();
  // Subject2: doSomething

  observer3Ptr->removeSubject();
  observer3Ptr->setSubject(subject2Ptr);

  subject1Ptr->doSomething();
  // Subject1: doSomething
  // Observer1: notify: doSomething
  // Observer2: notify: doSomething

  subject2Ptr->doSomething();
  // Subject2: doSomething
  // Observer3: notify: doSomething

  return 0;
}