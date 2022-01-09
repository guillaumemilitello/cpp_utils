#pragma once

#include <atomic>
#include <condition_variable>

class Mutex // spinlock
{
    std::atomic_flag _flag;

public:
    Mutex(): _flag(ATOMIC_FLAG_INIT) {}

    void lock()
    {
        while(_flag.test_and_set(std::memory_order_acquire));
    }

    void unlock()
    {
        _flag.clear(std::memory_order_release);
    }
};

class SharedMutex
{
     Mutex _mutex;
     int _readers = 0;
     bool _writer = false;
     std::condition_variable_any _unlocked;

public:
     SharedMutex() = default;
     SharedMutex(const SharedMutex &) = delete;
     SharedMutex &operator=(const SharedMutex &) = delete;

     void read_lock()
     {
          _mutex.lock();
          while (_writer)
          {
               _unlocked.wait(_mutex);
          }
          ++_readers;
          _mutex.unlock();
     }

     void read_unlock()
     {
          _mutex.lock();
          --_readers;
          if (_readers == 0)
          {
               _unlocked.notify_all();
          }
          _mutex.unlock();
     }

     void write_lock()
     {
          _mutex.lock();
          while (_writer || _readers > 0)
          {
               _unlocked.wait(_mutex);
          }
          _writer = true;
          _mutex.unlock();
     }

     void write_unlock()
     {
          _mutex.lock();
          _writer = false;
          _unlocked.notify_all();
          _mutex.unlock();
     }
};

class ScopedReadLock
{
     SharedMutex& _mutex;

public:
     ScopedReadLock(SharedMutex& mutex_) : _mutex(mutex_)
     {
          _mutex.read_lock();
     }

     ~ScopedReadLock()
     {
          _mutex.read_unlock();
     }
};

class ScopedWriteLock
{
     SharedMutex& _mutex;

public:
     ScopedWriteLock(SharedMutex& mutex_) : _mutex(mutex_)
     {
          _mutex.write_lock();
     }

     ~ScopedWriteLock()
     {
          _mutex.write_unlock();
     }
};

