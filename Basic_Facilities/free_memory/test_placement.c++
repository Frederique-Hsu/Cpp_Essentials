/*!
 *  \file       test_placement.c++
 *  \brief
 *
 */


#include "placement.hpp"

#include <gtest/gtest.h>

TEST(UTest4Placement, CheckHowPlacementNewWorks)
{
    void* buf = reinterpret_cast<void*>(0xF00F);    // 一个明确的地址
    X* px = new(buf) X(3);  // 在buf处构建X的对象，调用 operator new(sizeof(X), buf);

    // do something...

    operator delete(buf, px);
}

TEST(UTest4Placement, CheckNoThrowNew)
{
    auto fn = [](int n) {
        int* p = new(std::nothrow) int[n];
        if (p == nullptr)
        {
            std::cout << "Failed to allocate the memory for array." << std::endl;
        }
        // do something...
        delete(std::nothrow, p);
    };

    fn(10);
}
