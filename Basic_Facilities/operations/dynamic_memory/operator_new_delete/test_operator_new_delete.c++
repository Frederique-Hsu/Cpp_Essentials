/*!
 *  \file       test_operator_new_delete.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <new>
#include <stdexcept>

#include "operator_new_delete.hpp"

TEST(UTester4OperatorNewDelete, CheckUserNewDelete)
{
    int* p1 = new int;
    delete p1;

    int* p2 = new int[10];
    delete [] p2;
}

TEST(UTester4OperatorNewDelete, CheckOverloadedOperatorNewInsideClass)
{
    X* p1 = new X;
    delete p1;

    X* p2 = new X[15];
    delete [] p2;
}

TEST(UTester4OperatorNewDelete, CheckReplacementNewOperator)
{
    GTEST_SKIP();

    void* buffer = reinterpret_cast<void*>(0xF00F);     // 一个明确的地址，但这个地址可能是无效地址，易导致程序崩溃.
    X* p2 = new(buffer) X;      // 在buffer处构建X, 调用 operator new(sizeof(X), buffer)

    delete p2;
}

TEST(UTester4OperatorNewDelete, CheckOperatorNewNoThrow)
{
    int* p = new(std::nothrow) int[5];
    if (p == nullptr)
    {
        throw std::bad_alloc();
    }
    std::cout << "p address = " << std::hex << p << std::endl;

    delete(std::nothrow, p);
}
