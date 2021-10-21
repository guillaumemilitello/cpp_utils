#pragma once

#include <functional>
#include <vector>
#include <thread>
#include <atomic>

#include "threadsafe_queue.h"


class Threadpool
{
    std::atomic<bool> _done;
    ThreadsafeQueue<std::function<void()>> _taskQueue;
    std::vector<std::thread> _threadVect;

    void process()
    {
        while(!_done)
        {
            std::function<void()> task;
            if (_taskQueue.try_pop(task))
            {
                try
                {
                    task();
                }
                catch(const std::exception &exc)
                {
                    // catch anything thrown within try block that derives from std::exception
                    std::cerr << exc.what();
                }
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }

public:
    Threadpool() : Threadpool(std::thread::hardware_concurrency())// @todo: check -1
    {}

    Threadpool(unsigned threadCount_) : _done(false)
    {
        try
        {
            for (unsigned i = 0; i < threadCount_; ++i)
            {
                _threadVect.push_back(std::thread(&Threadpool::process, this));
            }
        }
        catch(...)
        {
            _done = true;
            throw;
        }
    }

    ~Threadpool()
    {
        _done = true;
        for (auto& thread : _threadVect)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }


    template <typename FunctionType, typename... Args>
    void submit(FunctionType&& f_, Args&&... args_)
    {
        _taskQueue.push([&](){ f_(std::forward<Args>(args_)...); });
    }
};
