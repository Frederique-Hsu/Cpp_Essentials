/*!
 *  \file       main.cpp
 *  \brief      This project will make an in-depth and comprehensive research on the
 *              explicit/implicit type conversion.
 *
 */


#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*!
 *  \title      显式与隐式类型转换
 *
 *  \details    C++编程的时候，我们有时必须把一种类型的值转换成另一种类型的值。
 *              很多情况下这种类型转换都是根据语言的规则隐式执行的。
 *  \code
 *              double d = 123456;      // 整数转换成浮点数，隐式自动进行转换的。
 *              int i = d;              // 浮点数转换成整数，也是隐式自动进行转换的。
 *  \endcode
 *
 *              但在另外一些情况下，我们必须显式地转换类型。
 */

/*!
 *  \section    C++提供多种显式类型转换的操作
 *
 *  \list
 *      \li     构造 - 使用{}符号提供对新值类型安全的构造
 *
 *      \list   命名的转换，提供不同等级的类型转换
 *
 *          \li const_cast - 对某些声明为const的对象转换为非const对象，使得可以对其进行写入。
 *
 *          \li static_cast - 反转一个定义良好的隐式类型转换
 *
 *          \li reinterpret_cast - 任意不同对象指针之间的转换
 *
 *          \li dynamic_cast - 动态地检查类层次关系
 *
 *      \endlist
 *
 *      \li     C风格的转换，提供命名的类型转换或其组合
 *
 *      \li     函数化符号，提供C风格转换的另一种形式
 *  \endlist
 */
