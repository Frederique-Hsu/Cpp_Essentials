/*!
 *  \file       test_free_memory.c++
 *  \brief
 *
 */


#include "free_memory.hpp"

#include <gtest/gtest.h>

#include <complex>

TEST(UTest4FreeMemory, CheckNewObjectInitialization)
{
    /*!
     *  \note   可以使用{}列表形式传递实参，当然也可以使用传统的()列表形式指定初始化器。
     *          但是，如果试图用符号=初始化一个用new创建的对象，将会引发程序错误。 如下：
     */
    // int* p = new int = 7;   // Error: the literal number 7 is not assignable.

    /*!
     *  \note   如果某一类型含有默认构造函数，则可以省略掉初始化器。但是对内置类型这么做的话，
     *          其变量将会处于未初始化的状态。
     */
    auto pc = new std::complex<double>;     //  该复数被初始化为{0, 0}
    EXPECT_DOUBLE_EQ(pc->real(), 0.0);
    EXPECT_DOUBLE_EQ(pc->imag(), 0.0);
    delete pc;

    auto pi = new int{};    // 该int被初始化为0
    EXPECT_EQ(*pi, 0);
    delete pi;
}

TEST(UTest4FreeMemory, CheckWhetherLocalObjectMoveToReturnedObject)
{
    std::string raw("hello");

    std::string reversed = reverse(raw);
    std::cout << "reversed address = " << &reversed << std::endl;

    EXPECT_STRCASEEQ(reversed.c_str(), "olleh");
}

TEST(UTest4FreeMemory, CheckSmartPointerPreventMemoryLeak)
{
    auto fn = [](int n) {
        int* p1 = new int[n];   // 存在潜在的内存泄漏风险

        std::unique_ptr<int[]> p2{new int[n]};  // 使用智能指针，则不存在内存泄漏。
        // do something
        if (n % 2)
        {
            throw std::runtime_error("odd");    // 即使异常抛出了，p2也会正确地释放了。
        }

        delete [] p1;   // 当中间发生一场抛出时，程序将运行不到此处。 p1就发生了内存泄漏。
    };

    EXPECT_THROW(fn(19), std::runtime_error);
}

TEST(UTest4FreeMemory, CheckAllocateArray)
{
    auto fn = [](int n) {
        std::vector<int>* p = new std::vector<int>(n);  // 单个对象
        int* q = new int[n];    // 数组

        // do something....

        delete p;
        delete [] q;
    };

    fn(5);
}
