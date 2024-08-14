/*!
 *  \file       test_macros.c++
 *  \brief
 *
 */


#include "macros.hpp"

#include <gtest/gtest.h>

TEST(UTest4Macros, InspectFlawsOfMacros)
{
#if true
    int x = 1;
    int y = 10;
    int z = macros::min(x++, y++);
    EXPECT_EQ(x, 2);
    EXPECT_EQ(y, 11);
    EXPECT_EQ(z, 1);
#else
    int x = 1;
    int y = 10;
    int z = MIN(x++, y++);  // 此处使用宏会产生错误，x变成了3（明显错误，我们期望的是x = 2）

    EXPECT_EQ(x, 2);
    EXPECT_EQ(y, 11);
    EXPECT_EQ(z, 2);
#endif
    std::cout << "x = " << x << std::endl
              << "y = " << y << std::endl
              << "z = " << z << std::endl;
}

TEST(UTest4Macros, CheckMacroStringifyAndConcatnate)
{
    NAME2(print, f)("This is the macro concatenate.\n");

    int a = 7;
    std::string str = "The C++ Programming Language.";

    auto fn = [=]() {
        PRINTX(a);
        PRINTX(str);
    };
    fn();

    EMPTY();
    ERR_PRINT("The answer is ", 54);
}

TEST(UTest4Macros, CheckPredefinedMacros)
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Today is " << __DATE__ << std::endl;
    std::cout << "Now is " << __TIME__ << std::endl;
    std::cout << "Current file name is " << __FILE__ << std::endl;
    std::cout << "Current code line no. is #" << __LINE__ << std::endl;
    std::cout << "Current function name is " << __FUNCTION__ << std::endl;
    std::cout << "Current implementation is hosted? " << __STDC_HOSTED__ << std::endl;

    std::printf("Current C standard no. is %d\n", __STDC__);

    std::cout << "Current program has multiple threads? " << __STDCPP_THREADS__ << std::endl;
}
