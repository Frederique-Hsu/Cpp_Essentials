/*!
 *  \file       sync_queue.hpp
 *  \brief
 *
 */


#pragma once

#include <mutex>
#include <condition_variable>
#include <list>

/* Declaration ===================================================================================*/
template<typename T>
class Sync_Queue
{
public:
    void put(const T& val);
    void put(T&& val);
    void get(T& val);
private:
    std::mutex mtx;
    std::condition_variable cond;
    std::list<T> q;
};



/* Implementation ================================================================================*/
template<typename T> void Sync_Queue<T>::put(const T& val)
{
    std::lock_guard<std::mutex> lck(mtx);
    q.push_back(val);
    cond.notify_one();
}

template<typename T> void Sync_Queue<T>::put(T&& val)
{
    std::lock_guard<std::mutex> lck(mtx);
    q.push_back(std::move(val));
    cond.notify_one();
}

template<typename T> void Sync_Queue<T>::get(T& val)
{
    std::unique_lock<std::mutex> lck(mtx);
    cond.wait(lck, [this]{ return !q.empty(); });
    val = q.front();
    q.pop_front();
}
