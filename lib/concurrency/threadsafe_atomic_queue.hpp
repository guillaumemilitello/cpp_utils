#pragma once

#include <atomic>
#include <memory>
#include <optional>

template<typename T>
class ThreadsafeAtomicQueue
{
  struct Node
  {
    T _data;
    Node* _next;
    Node() : _next(nullptr) {}
    Node(const T& data_) : _data(data_) {}
    Node(T&& data_) : _data(std::move(data_)) {}
  };

  std::atomic<Node*> _head;
  std::atomic<Node*> _tail;

public:
  ThreadsafeAtomicQueue() : _head(nullptr), _tail(nullptr) {}

  ThreadsafeAtomicQueue(const ThreadsafeAtomicQueue<T> &) = delete ;
  ThreadsafeAtomicQueue& operator=(const ThreadsafeAtomicQueue<T> &) = delete ;

  ~ThreadsafeAtomicQueue()
  {
    while(Node* const oldHead = _head.load())
    {
      _head.store(oldHead->_next);
      delete oldHead;
    }
  }

  std::optional<T> pop()
  {
    Node* const oldHead = _head.load();
    if (!oldHead)
    {
      return {};
    }
    _head.store(oldHead->_next);
    T res(std::move(oldHead->_data));
    delete oldHead;
    return res;
  }

  void push(const T& value_)
  {
    Node* p {new Node(value_)};
    Node* const oldTail = _tail.load();
    if (oldTail)
    {
      oldTail->_next = p;
    }
    _tail.store(p);
    Node* const oldHead = _head.load();
    if (!oldHead)
    {
      _head.store(p);
    }
  }

  void push(T&& value_)
  {
    Node* p {new Node(std::move(value_))};
    Node* const oldTail = _tail.load();
    if (oldTail)
    {
      oldTail->_next = p;
    }
    _tail.store(p);
    Node* const oldHead = _head.load();
    if (!oldHead)
    {
      _head.store(p);
    }
  }
};
