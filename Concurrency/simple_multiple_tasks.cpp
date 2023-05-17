/*!
 *  \file       main.cpp
 *  \brief      Try to study the concurrency mechanism of C++ program.
 *
 */



#include <thread>
#include <iostream>

void fnct();        // 函数

struct Functor      // 函数对象
{
    void operator()();
};


int main()
{
    std::thread fnct_thread{fnct};              // 费fnct()在独立的线程中执行
    std::thread functor_thread{Functor()};      // Functor()()在独立的线程中执行

    fnct_thread.join();         // 等待fnct_thread完成
    functor_thread.join();      // 等待functor_thread完成

    return 0;
}

void fnct()
{
    std::cout << "Hello ";
}

void Functor::operator()()
{
    std::cout << "Parallel World!\n";
}
