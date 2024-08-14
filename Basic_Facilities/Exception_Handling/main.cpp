/*!
 *  \file       main.cpp
 *  \brief      This project will dive into the exception handling subject in C++.
 *
 */



#include <gtest/gtest.h>

using namespace std;

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*!
 *  \title      错误处理
 *
 *  \section    异常安全保障 (exception-safety guarantee), 它是程序从运行时错误中快速恢复的关键。
 *
 *  \section    使用构造函数和析构函数进行资源管理的资源获取即初始化 (Resource Acquisition Is Initialization,
 *              RAII)技术。
 */


/*!
 *  \subtitle   异常 exception
 *
 *  \brief      异常的概念可以帮助我们将信息从检测到错误的地方传递到处理该错误的地方。
 *              如果函数无法处理某个问题，则抛出(throw)异常，并且寄希望于函数的调用者能直接或间接地处理该问题。
 *              函数如果希望处理某个问题，可以捕获(catch)相应的异常。
 *
 *  \list
 *      \li     主调组件如果想处理某些失败的情形，可以把这些异常置于try块的catch从句中。
 *
 *      \li     被调组件如果无法完成既定的任务，可以用throw表达式抛出一个异常来说明这一情况。
 *  \endlist
 */

/*! \brief  This is the callee */
int do_task()
{
    bool start;
    std::cin >> start;
    if (start)
    {
        return int{};
    }
    else
    {
        throw std::runtime_error("Failed to execute this task.");
    }
}

/*! \brief  This is the caller */
void taskmaster()
{
    try
    {
        auto result = do_task();
        std::cout << "The result is " << result << std::endl;
    }
    catch (std::runtime_error& err)
    {
        std::cout << "Error: " << err.what() << std::endl;
    }
}

/*!
 *  \attention  一个被调用的函数不能仅仅报告错误就了事。
 *              如果程序想继续运行下去，而非仅仅输出一条错误信息后终止，则函数返回的同时必须确保程序的状态良好且
 *              没有泄漏任何资源。
 *
 *              C++的异常处理机制与构造函数/析构函数机制以及并发机制一道为这一目标提供了保障。
 *
 *  \subtitle   异常处理机制
 *
 *  \list
 *      \li     是对传统技术的一次改进，传统技术常常低效、粗糙且充满了错误风险。
 *      \li     是完备的，它能处理普通代码中发生的各类问题。
 *      \li     允许程序员显式地把错误处理代码从“普通代码”中分离出来，从而提高了程序的可读性，也便于使用辅助工具。
 *      \li     提供了一种更规范的错误处理机制，使得多个单独编写的程序片段合作起来更容易了。
 *  \endlink
 */
