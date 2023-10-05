/*!
 *  \file       main.cpp
 *  \brief
 *
 */



#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*!
 *  \title      函数
 *
 *  \subtitle   函数声明： 定义函数的过程就是描述某项操作应该如何执行的过程。
 *                       函数声明负责指定函数的名字，返回值的类型以及调用该函数所需的参数数量和类型。
 *
 *
 *  \note       函数声明的组成条件：
 *
 *  \list
 *      \li     函数的名字： 必选
 *      \li     参数列表，可以为空(); 必选
 *      \li     返回类型，可以为vois, 可以是前置或后置（使用auto），必选
 *      \li     inline, 表示一种愿望，通过内联函数体实现函数调用
 *      \li     constexpr，表示当给定常量表达式作为实参时，应该可以在编译时对函数求值。
 *      \li     noexcept，表示该函数不允许抛出异常
 *      \li     链接说明，如static
 *      \li     [[noreturn]], 表示该函数不会用常规的调用/返回机制返回结果
 *      \li     virtual, 表示该函数可以被派生类覆盖
 *      \li     override,表示该函数必须覆盖基类中的一个虚函数
 *      \li     final, 表示该函数不能被派生类所覆盖
 *      \li     static, 表示该函数不与某一个特定的对象关联
 *      \li     const, 表示该函数不能修改其对象的内容
 *  \endlist
 */

struct S
{
    [[noreturn]] virtual inline auto f(const unsigned long int *const) noexcept -> void const;
};
