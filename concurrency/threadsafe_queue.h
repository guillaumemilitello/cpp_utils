#pragma once

#include <mutex>
#include <queue>
#include <optional>
#include <condition_variable>

template<typename T>
class ThreadsafeQueue
{
  mutable std::mutex _mutex;
  std::queue<T> _queue;
  std::condition_variable _condvar;

public:
  ThreadsafeQueue() = default;
  ThreadsafeQueue(const ThreadsafeQueue<T> &) = delete ;
  ThreadsafeQueue& operator=(const ThreadsafeQueue<T> &) = delete ;

  bool wait_pop(T& value_, std::chrono::milliseconds timeout_=std::chrono::milliseconds(1000))
  {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_condvar.wait_for(lock, timeout_, [this]{ return !_queue.empty(); }))
    {
      return false;
    }
    value_ = std::move(_queue.front());
    _queue.pop();
    return true;

  }

  bool try_pop(T& value_)
  {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_queue.empty())
    {
      return false;
    }
    value_ = std::move(_queue.front());
    _queue.pop();
    return true;
  }

  std::optional<T> pop()
  {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_queue.empty())
    {
      return {};
    }
    T res {_queue.front()};
    _queue.pop();
    return res;
  }

  void push(T&& value_)
  {
    std::unique_lock<std::mutex> lock(_mutex);
    _queue.push(std::move(value_));
    _condvar.notify_one();
  }

  bool empty() const
  {
    std::unique_lock<std::mutex> lock(_mutex);
    return _queue.empty();
  }

  size_t size() const
  {
    std::unique_lock<std::mutex> lock(_mutex);
    return _queue.size();
  }

};
