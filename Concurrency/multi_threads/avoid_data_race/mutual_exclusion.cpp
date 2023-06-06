/*!
 *  \file       mutual_exclusion.cpp
 *  \brief
 *
 */


#include "mutual_exclusion.hpp"

#include <vector>
#include <list>

std::mutex count_mutex;

void hello()
{
    count_mutex.lock();
    std::cout << "Hello, ";
    count_mutex.unlock();
}

void world()
{
    count_mutex.lock();
    std::cout << "World! ";
    count_mutex.unlock();
}


void composer()
{
    static std::mutex wqm;
    static std::list<Work> work_queue;

    std::list<Work> requests;

    while (true)
    {
        for (int index = 0; index != 10; ++index)
        {
            Work work;
            // ... 生成工作请求 ...
            requests.push_back(work);
        }
        if (wqm.try_lock())
        {
            work_queue.splice(work_queue.begin(), requests);
            wqm.unlock();
        }
    }
}

void use_lock_guard(std::mutex& mtx, std::vector<std::string>& vs, int i)
{
    if (i < 0)
        return;

    std::string s;
    {
        std::lock_guard<std::mutex> g{mtx};
        s = vs[i];
    }
}

void use_timed_lock()
{
    std::timed_mutex tmtx;

    std::unique_lock<std::timed_mutex> lck(tmtx, std::chrono::milliseconds(2));

    if (lck.owns_lock())
    {
        // acquire the lock successfully, do something here
    }
    else
    {
        // failed to acquire the lock, time-out.
        // do something else.
    }
}
