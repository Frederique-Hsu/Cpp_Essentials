/*!
 *  \file       test_producer_consumer.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <thread>
#include <iostream>

#include "producer_consumer.hpp"
#include "utils.hpp"

TEST(UTester4ProducerConsumerModel, OrganizeProducerConsumerWithDifferentThreads)
{
    Sync_queue<Message> mesg_queue;
    Producer producer(mesg_queue);
    Consumer consumer(mesg_queue);

    Message mesg = {"Frederique Hsu", 12000};
    std::thread prod_thrd(producer, std::ref(mesg));
    std::thread cons_thrd(consumer);

    std::cout << "prod_thrd thread-id = " << prod_thrd.get_id() << std::endl;
    std::cout << "cons_thrd thread-id = " << cons_thrd.get_id() << std::endl;

    prod_thrd.join();
    cons_thrd.join();

    std::cout << "this_thread id = " << std::this_thread::get_id() << std::endl;
    /*!
     *  Since prod_thrd and cons_thrd have ended the execution.
     *
     *  \remark     每个执行线程都有唯一标识符，用`std::thread::id`类型的值表示。
     *              如果一个`std::thread thrd`不表示一个执行线程，则其id默认为`std::thread::id{}`空的
     *              一个`std::thread thrd`的id可以通过调用`thrd.get_id()`获得。
     *
     *              当前thread的id可以通过`std::this_thread::get_id()`获得。
     *
     *  \note       在下列情况下，一个thread的id可以是空`id{}`:
     *              1.  它未被赋予一个任务
     *              2.  它已结束
     *              3.  它已被移动
     *              4.  它已被`detach()`
     *
     *              每个thread都有一个id， 但一个系统线程仍可以在没有id的情况下运行，即`detach()`之后
     */
    print_thread_id(prod_thrd);
    print_thread_id(cons_thrd);
}
