/*!
 *  \file       main.cpp
 *  \brief      This file implements the main() portal function for current project.
 *
 */


#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    for (int index = 0; index < argc; ++index)
    {
        std::cout << "argv[" << index << "] = " << argv[index] << std::endl;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*================================================================================================*/

struct S
{
    [[noreturn]] virtual inline auto f(const unsigned long int* const) noexcept -> void const;
};


/*!
 *  \remark     对于大多数程序员来说，函数的规模最好控制在大约40行以内。
 *
 *              最理想的函数规模更小，平均7行左右。
 */


/*!
 *  \section    函数的声明的组成要件
 *
 *  \list
 *      \li     函数的名字； 必选
 *      \li     参数列表，可以为空(), 必选
 *      \li     返回类型，可以是void, 可以是前置或者后置形式（如使用auto），必选
 *      \li     inline, 表示一种愿望：通过内联函数体实现函数调用
 *      \li     constexpr, 表示当给定常量表达式作为实参时，应该可以在编译时对函数求值
 *      \li     noexcept, 表示该函数不会抛出异常
 *      \li     [[noreturn]], 表示该函数不会用常规的调用/返回机制返回结果
 *      \list   成员函数
 *          \li virtual, 表示该函数可以被派生类覆盖
 *          \li override, 表示该函数必须覆盖基类中的一个虚函数
 *          \li final, 表示该函数不能被派生类覆盖
 *          \li static，表示该函数是一个静态函数，是一个类方法，不需要实例化一个对象来调用
 *          \li const, 表示该函数不能修改其对象的内容
 *      \endlist
 *  \endlist
 *
 *  构造函数 constructor, 严格说不是函数，它没有返回值，可以初始化基类和成员，无法得到其地址
 *
 *  析构函数 destructor, 不能被重载，无法得到其地址, 不能有参数，无法得到其地址
 *
 *  函数对象 function object, 不是函数，而是对象，不能被重载，但是其operator()是函数
 *
 *  lambda表达式，是定义函数对象的一种简写形式。它是对象。
 */
