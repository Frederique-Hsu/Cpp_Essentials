/*!
 *  \file       main.cpp
 *  \brief      Make the research on how to manage threads
 *
 */


#include <iostream>
#include <thread>

#include "background_task.hpp"

/*!
 *  \details    每个程序至少有一个线程：执行\code main() \endcode 函数的线程，其余线程有各自的入口函数。
 */
int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    /*!
     *  \note   简单地传入 std::thread 一个函数名，即可启动一个线程。
     */
    std::thread my_thread(doSomething);

    /*!
     *  \note   std::thread 可以用“可调用类型构造”，将带有函数调用符类型的实例对象传入，替换默认的构造函数。
     */
    BackgroundTask fn;
    std::thread fn_thread(fn);

    /*!
     *  \note   如果你传递一个临时变量，而不是一个命名的变量。 C++编译器会将其解析为函数声明，而不是类型对象的定义。
     *
    std::thread invalid_thread(BackgroundTask());
     *
     *  \note   但使用uniform-initializer统一初始化语法（即object{}， 如下的valid_thread），却可以启动一个线程。
     *          也可以使用多组括号。
     */
    std::thread valid_thread{BackgroundTask()};
    // std::thread valid_thread((BackgroundTask()));

    /*!
     *  \note   使用lambda表达式来作为线程的函数，如下的lambda_thread，也可以启动一个线程。
     */
    std::thread lambda_thread([]() {
        doSomething();
        doSomethingElse();
    });


    /*!
     *  \note   启动了线程，你需要明确是等待线程结束（加入式），还是让其自主运行（分离式）？
     *          如果 std::thread 对象销毁之前还没有做出决定，程序就会终止（std::thread的析构函数会调用std::terminate()）.
     *
     *          因此，即便有异常存在，也要确保线程能够正确的加入（joined）或分离（detached）.
     *          需要注意的是，必须在std::thread对象销毁之前做出决定，否则你的程序将会终止。这时再去决定会触发相应异常。
     */
    my_thread.join();
    fn_thread.join();
    valid_thread.join();
    lambda_thread.join();

    return EXIT_SUCCESS;
}
