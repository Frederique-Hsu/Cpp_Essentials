/*!
 *  \file       multi_threads.hpp
 *  \brief
 *
 */



#pragma once

#include <future>
#include <vector>

class Message
{
};


void consumer();
void producer();

/*!
 *  \brief      一个发送者任务，将结构放在send_mesg中
 *  \param      send_mesg
 */
void sender_task(std::promise<Message>& send_mesg);
/*!
 *  \brief      一个接收者任务，从get_mesg中获取结果
 *  \param      get_mesg
 */
void receiver_task(std::future<Message>& get_mesg);
/*!
 *  \brief      计算[begin, end)中元素的和，计算的初始值是init
 *  \param      begin - 容器的begin迭代器
 *  \param      end - 容器的end迭代器
 *  \param      init_value - 初始值
 */
double accum(double* begin, double* end, double init_value);
/*!
 *  \brief      计算vec容器中的所有元素之和，但容器中的元素太多，为提高效率，分成两个任务同时进行计算，
 *              最后合并两个任务的计算结果。
 *  \param      vec - vector<double>的容器
 */
double dual_tasks_parallel_compute(std::vector<double>& vec);
/*!
 *  \brief      计算vec容器中的所有元素之和，使用async将计算任务拆分为4个，分4段来计算各自的累积和，
 *              最后进行汇总。
 *  \param      vec - vector<double>的容器
 */
double quad_tasks_async_compute(std::vector<double>& vec);

void print_thread_id(std::thread& thrd);
