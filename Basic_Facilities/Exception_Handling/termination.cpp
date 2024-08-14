/*!
 *  \file       termination.cpp
 *  \brief
 *
 */


#include "termination.hpp"
#include "throw_catch_exception.hpp"

#include <exception>
#include <iostream>
#include <future>
#include <cmath>

[[noreturn]] void my_handler()  // 终止处理程序无法返回任何值
{
    // 自行处理终止
}

void dangerous()
{
    terminate_handler old = std::set_terminate(my_handler);

    std::set_terminate(old);    // 修复旧的终止处理程序
}

/*!
 *  \note   如果在发生未捕获的异常时，你希望程序能够执行某些清理工作，你可以在真正在意的处理程序之外再向名main()
 *          添加一个捕获全部异常的处理程序。
 *
 *          如下这个main_fn()程序将捕获几乎全部异常，只有名字空间和线程局部对象的构造和析构抛出的异常除外。
 *
 *          任何措施都无法捕获在名字空间和线程局部对象的初始化及析构过程中抛出的异常。
 *          这恰恰是我们应该尽量避免使用全局变量的另一个原因。
 */
int main_fn()
{
    try
    {
        // ...
    }
    catch (const MyError& err)
    {
        // ... handle the error
    }
    catch (const std::range_error&)
    {
        std::cerr << "rnage error: Not again!\n";
    }
    catch (const std::bad_alloc&)
    {
        std::cerr << "new ran out of memory." << std::endl;
    }
    catch (...)
    {
        // ... handle with any other exceptions.
    }
    exit(EXIT_FAILURE);
}

/*!
 *  \subsection 异常与线程
 *
 *  \details    如果异常在线程中未被捕获，系统将调用std::terminate().
 *              因此，如果我们不希望整个程序因线程中的一个错误就终止执行，就必须捕获全部错误并且以某种方式把他们
 *              报告给主程序中对线程执行结果感兴趣的部分。
 *
 *              我们可以用标准库函数 current_exception把某一线程的异常传递给另一个线程的处理程序.
 */

#include <gtest/gtest.h>

TEST(UTest4ExceptionInsideThread, CheckHowToHandleExceptionInsideThread)
{
    std::promise<int> prom;
    std::future<int> futr = prom.get_future();

    std::thread thrd([&prom]() {
        try
        {
            throw std::runtime_error("Example");
        }
        catch (...)
        {
            try
            {
                prom.set_exception(std::current_exception());
            }
            catch (...)
            {
            }
        }
    });

    try
    {
        std::cout << futr.get();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception from the thread: " << e.what() << std::endl;
    }
    thrd.join();
}
