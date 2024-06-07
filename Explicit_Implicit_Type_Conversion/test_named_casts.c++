/*!
 *  \file       test_named_casts.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>

#include <complex>

/*!
 *  \section    命名转换
 *
 *  \details    有的类型转换行为不够良好或者无法进行类型检查，他们所转换的值并非来源于定义良好的值的集合。
 *
 *  \codeline   IO_device* dev = reinterpret_cast<IO_device*>(0xFF00);
 *
 *              编译器并不能确定整数0xFF00是否是一个有效的(I/O设备寄存器)地址，因此，这条转换语句的正确性完全
 *              依赖于程序员自己。
 *
 *              显式类型转换也称为强制类型转换(casting)，只有在极个别的情况下才有用。然而在过去，显式类型转换被严重
 *              滥用了，成为程序错误的主要来源。
 */


TEST(UTest4NamedCasts, CheckHowNameCastsWork)
{
    class IO_device
    {
    };

    IO_device* dev = reinterpret_cast<IO_device*>(0xFF00);
    EXPECT_NE(dev, nullptr);
}

/*!
 *  \section    四大命名的类型转换
 *
 *  \list
 *      \li     static_cast 执行关联类型之间的转换
 *
 *              比如： 1) 一种指针类型向同一个类层次中其他指针类型的转换
 *                    2) 整数类型向枚举类型的转换
 *                    3) 浮点类型向整数类型的转换
 *                    4) 执行构造函数和转换运算符定义的类型转换
 *
 *      \li     reinterpret_cast 处理非关联类型之间的转换。通常情况下，它产生的新类型的值与它的实参具有相同的位模式。
 *              如果目标值所占的位数不少于原始值，则我们可以把结果reinterpret_cast再返回它的原始类型。
 *              只有当reinterpret_cast的结果能够被精确地转换回原始类型时，该结果才是可用的。
 *              注意：reinterpret_cast必须作用于函数指针。
 *
 *              比如： 1）整数向指针的转换
 *                    2) 指针向另一个非关联指针类型的转换
 *
 *      \li     const_cast 参与转换的类型仅在const修饰符和volatile修饰符上有区别
 *
 *      \li     dynamic_cast 执行指针或者引用向类层次体系的类型转换，并执行运行时检查。
 *  \endlist
 */

TEST(UTest4NamedCasts, CheckFourTypeCasts)
{
    char x = 'a';
    // int* p1 = &x;       // Error: 不存在char*向int*的隐式类型转换
    // int* p2 = static_cast<int*>(&x);    // 也是错误：不存在char*向int*的显式类型转换
    int* p3 = reinterpret_cast<int*>(&x);   // OK: 但该转换可能出错，由程序员负责
    EXPECT_NE(*p3, x);

    struct B
    {
    };

    struct D : B
    {
    };

    B* pb = new D;
    // D* pd = pb;     // 错误： 不存在B*向D*的隐式类型转换
    D* pd = static_cast<D*>(pb);    // OK
    EXPECT_EQ(pd, pb);
    std::cout << "pb = " << pb << "\npd = " << pd << std::endl;
    delete pb;
}

/*!
 *  \section    C风格的类型转换    (T)e
 *
 *  \brief      (T)e : 它的含义是从表达式e得到类型为T的值
 *
 *              (T)e可能是执行关联类型之间的可移植转换，也可能是非关联类型之间的不可移植的类型转换，
 *              还有可能是移除指针类型前面的const修饰符号
 */

/*!
 *  \section    函数形式的转换     T(e)
 *
 *  \brief      用值e构建类型T的值的过程可以表示为函数形式的符号T(e)
 *
 *              即使从一种较长的整数类型向较短的整数类型（如 long -> char）的显式类型转换也会导致不可移植的
 *              依赖于实现的行为。
 *
 *              建议用T{v}处理行为良好的构造，用命名的转换(比如static_cast)处理其他任务。
 */

TEST(UTest4NamedCasts, CheckFunctionStyleCast)
{
    auto fn = [](double d, char* p) -> void {
        int i = int(d);     // d值被截断了

        std::complex z = std::complex(d);   // 从d构建一个complex

        int b = int(*p);    // 不可移植
    };
}
