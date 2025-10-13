/*!
 *  \file       transferring_threads.cpp
 *  \brief
 *
 */


#include "transferring_threads.hpp"
#include "ScopedThread.hpp"
#include "Functor.hpp"

#include <iostream>
#include <thread>
#include <vector>

#define UNUSED(arg)     (void)arg

void someFunction()
{
    std::cout << "performing someFunction()..." << std::endl;
}

void otherFunction()
{
    std::cout << "performing otherFunction()..." << std::endl;
}


void moveBetweenThreads()
{
    std::thread t1(someFunction);

    // 显式使用std::move()创建t2后，t1的所有权就转移给t2了。 之后，t1和执行线程没有关联了；
    // 执行someFunction()的函数现在与t2关联。
    std::thread t2 = std::move(t1);

    // t1与一个临时的std::thread对象相关的线程启动了。
    // 为什么不显式调用std::move()转移所有权呢？ 因为，所有者是一个临时对象--移动操作将会隐式调用。
    t1 = std::thread(otherFunction);

    // t3使用默认构造方式创建，与任何执行线程都没有关联。
    std::thread t3;

    // 调用std::move()将与t2关联线程的所有权转移给t3
    // 因为t2是一个命名对象，需要显式调用std::move()
    t3 = std::move(t2);
    // 移动操作完成后，t1与执行otherFunction()的线程想关联，t2与任何线程都无关联，t3与执行someFunction()相关联。

    // 最后一个移动操作，将someFunction()线程的所有权转移给t1.
    // 不过，t1已经有了一个关联的线程（otherFunction()），所以这里系统会直接调用 std::terminate() 终止程序继续运行。
    // 这样做（std::terminate() noexcept不抛出）是为了保证与 std::thread 的析构函数的行为一致。
    t1 = std::move(t3);


    /*!
     *  \note   需要在线程对象被析构前，显式的等待线程完成，或者分离它。
     *          进行赋值时也需要满足这些条件。 不能通过赋一个新值给 std::thread 对象的方式来丢弃一个线程。
     */
}

std::thread f_thread()
{
    auto fn = []()
    {
        std::cout << "This is the \"fn\" function of f_thread" << std::endl;
    };
    return std::thread(fn);
}

std::thread g_thread()
{
    auto gc = [](int)
    {
        std::cout << "This is the \"gc\" function of g_thread" << std::endl;
    };
    std::thread task(gc, 42);
    return task;
}

void f(std::thread t)
{
    t.join();
}

void g()
{
    auto someFn = []()
    {
        std::cout << "This is the \"someFn\" lambda function" << std::endl;
    };

    f(std::thread(someFn));
    std::thread task(someFn);
    std::cout << "Transferring the ownership of thread(id = " << task.get_id() << ")..." << std::endl;
    f(std::move(task));
}


void transferThreadOwnership()
{
    g();
}

void checkScopedThread()
{
    int local_state;
    ScopedThread task{std::thread(Functor(local_state))};

    auto doSomethingInCurrentThread = []() {
        std::cout << "Do something in current thread." << std::endl;
    };
    doSomethingInCurrentThread();

}

void spawnThreadsAndWaitCompletion()
{
    auto doWork = [](unsigned id) {
        std::cout << "Doing the " << id << "-th work item..." << std::endl;
    };

    std::vector<std::thread> threads;
    for (unsigned i = 0; i < 20; ++i)
    {
        threads.emplace_back(doWork, i);            // Spawns the threads
        // threads.push_back(std::thread(doWork, i));  // you can also write like this
    }

    for (std::thread& thread : threads)    // Call join() on each thread in turn
    {
        thread.join();
    }

    // std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));  // same as above
}
