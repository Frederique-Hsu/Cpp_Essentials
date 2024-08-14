/*!
 *  \file       test_type_cast.c++
 *  \brief
 *
 */


#include <CppUTest/TestHarness.h>

#include <cfloat>
#include <limits>
#include <iostream>

TEST_GROUP(UTester4TypeCast)
{
public:
    void f(double d)
    {
        char c = d;     // 当心： 这是双精度浮点数向字符类型的转换
        (void)c;    // 抑制 Unused variable 编译警告
        /*!
         *  \note   使用{}列表可以防止窄化计算的发生。
         */
        // char ch{d};     // 错误： 编译器发现程序试图把双精度浮点数转换成字符类型
    }
};

TEST(UTester4TypeCast, CheckFloatTypeCast)
{
    float f = FLT_MAX;      // 最大的单精度浮点值
    double d = f;
    std::cout << "sizeof(float) = " << sizeof(float) << std::endl;
    std::cout << "sizeof(double) = " << sizeof(double) << std::endl;
    std::cout << "FLT_MAX = " << FLT_MAX << std::endl;
    CHECK_EQUAL(d, f);

    double maxd = DBL_MAX;  // 最大的双精度浮点值
    float fvalue = maxd;    // 如果FLT_MAX < DBL_MAX，则结果未定义
    std::cout << "DBL_MAX = " << DBL_MAX << std::endl;
    CHECK_FALSE(fvalue == maxd);
    std::cout << "fvalue = " << fvalue << std::endl;

    long double ld = maxd;
    long double ld_max = std::numeric_limits<long double>::max();
    std::cout << "sizeof(long double) = " << sizeof(long double) << std::endl;
    std::cout << "ld_max = " << ld_max << std::endl;
    std::cout << "ld = " << ld << std::endl;

    double dvalue = ld_max;
    std::cout << "dvalue = " << dvalue << std::endl;
    CHECK_FALSE(dvalue == ld_max);
}

TEST(UTester4TypeCast, CheckPointerAndReferenceCast)
{
/*!
 *  \note   指针与引用类型转换
 *
 *  \list
 *      \li     任何指向对象类型的指针都能隐式地转换成void*
 *
 *      \li     指向派生类的指针（或引用）能隐式地转换成指向其可访问的且明确无二义的基类的指针（或引用）
 *
 *      \li     请注意，指向函数的指针和指向成员的指针不能隐式地转换成void*
 *
 *      \li     求值结果为0的常量表达式能隐式地转换成任意指针类型的空指针
 *
 *      \li     T* 可以隐式地转换成const T*
 *
 *      \li     T& 能隐式地转换成const T&
 *  \endlist
 */
}
