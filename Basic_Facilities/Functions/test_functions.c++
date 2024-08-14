/*!
 *  \file       test_functions.c++
 *  \brief      Make the unit test for functions.
 *
 */


#include <gtest/gtest.h>

#include "functions.hpp"

TEST(UTest4Functions, CheckSwapFunction)
{
    int a = -10, b = 5;
    swap(&a, &b);

    EXPECT_EQ(a, 5);
    EXPECT_EQ(b, -10);
}

TEST(UTest4Functions, CheckStaticLocalVariable)
{
    /*!
     *  \remarks    static局部变量有一个非常重要的作用，即：它可以在函数的多次调用间维护一份公共信息，而无须使用全局变量。
     *              如果使用了全局变量，则有可能会被其他不相关的函数访问甚至干扰。
     *
     */
    auto fn = [](int a) {
        while (a--)
        {
            /*!
             *  \note   当把局部变量声明成tatic, 则在函数的所有调用中都将使用唯一的一份
             *          静态分配的对象，该对象在线程第一次到达它的定义处时被初始化。
             */
            static int n = 0;
            int x = 0;      // 每次调用fn()时都会初始化

            std::cout << "n == " << n++ << ", x = " << x++ << std::endl;
        }
    };

    fn(3);
}

/*!
 *  \note       除非你进入一个递归调用的函数发生死锁，通常情况，static局部变量的初始化不会导致数据竞争。
 *              也就是说，C++实现必须用某种无锁机制（比如call_once）确保局部static变量的初始化能被正确执行。
 *              递归地初始化一个局部static变量将产生未定义的结果。
 *
 *              static局部变量有助于避免非局部变量间的顺序依赖。
 */
int recurse(int n)
{
    static int n1 = n;
    static int n2 = recurse(n-1) + 1;   // 未定义的
    return n;
}
