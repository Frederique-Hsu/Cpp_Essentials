/*!
 *  \file       multi_threads.cpp
 *  \brief
 *
 */


#include "multi_threads.hpp"

#include <mutex>
#include <queue>
#include <condition_variable>
#include <numeric>
#include <iostream>


std::queue<Message> mesg_queue;     // 消息的队列
std::condition_variable mcond;      // 通信用的条件变量
std::mutex mtx;                     // 锁机制

void consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lck(mtx);      // 获取锁
        mcond.wait(lck);    // 释放lck并等待，被唤醒后重新获取lck

        auto message = mesg_queue.front();      // 获取消息
        mesg_queue.pop();

        lck.unlock();       // 释放 lck
    }
}

void producer()
{
    while (true)
    {
        Message mesg;

        std::unique_lock<std::mutex> lck(mtx);      // 保护队列上的操作
        mesg_queue.push(mesg);

        mcond.notify_one();     // 通知，释放锁
    }
}

void sender_task(std::promise<Message>& send_mesg)
{
    try
    {
        Message mesg;

        send_mesg.set_value(mesg);
    }
    catch (...)
    {
        send_mesg.set_exception(std::current_exception());
    }
}

void receiver_task(std::future<Message>& get_mesg)
{
    try
    {
        Message mesg = get_mesg.get();
    }
    catch (...)
    {
    }
}

double accum(double* begin, double* end, double init_value)
{
    return std::accumulate(begin, end, init_value);
}

double dual_tasks_parallel_compute(std::vector<double>& vec)
{
    using Task_type = double(double*, double*, double);         // 任务的类型

    std::packaged_task<Task_type> ptask_first_half(accum);      // 打包任务 (即accum)
    std::packaged_task<Task_type> ptask_last_half(accum);

    std::future<double> future_first_half(ptask_first_half.get_future());   // 获取first_half的future
    std::future<double> future_last_half(ptask_last_half.get_future());     // 获取last_half的future

    double* first_ptr = &vec[0];

    std::thread thread_first_half(std::move(ptask_first_half),      // 为first_half启动一个线程
                                  first_ptr,
                                  first_ptr + vec.size()/2,
                                  0);
    std::thread thread_last_half(std::move(ptask_last_half),        // 为last_half启动一个线程
                                 first_ptr + vec.size()/2,
                                 first_ptr + vec.size(),
                                 0);

    thread_first_half.join();
    thread_last_half.join();

    return future_first_half.get() + future_last_half.get();    // 获取两个任务的结果
}

double quad_tasks_async_compute(std::vector<double>& vec)
{
    auto begin_pointer = &vec[0];
    auto length = vec.size();

    auto future_task1 = std::async(accum, begin_pointer                 , begin_pointer +       length/4, 0.0);
    auto future_task2 = std::async(accum, begin_pointer +       length/4, begin_pointer +       length/2, 0.0);
    auto future_task3 = std::async(accum, begin_pointer +       length/2, begin_pointer + length * 3 / 4, 0.0);
    auto future_task4 = std::async(accum, begin_pointer + length * 3 / 4, begin_pointer +         length, 0.0);

    return future_task1.get() + future_task2.get() + future_task3.get() + future_task4.get();
}

void print_thread_id(std::thread& thrd)
{
    if (thrd.get_id() == std::thread::id{})
    {
        std::cout << "This thread is not joinable." << std::endl;
    }
    else
    {
        std::cout << "This thread's id is " << thrd.get_id() << std::endl;
    }
}
