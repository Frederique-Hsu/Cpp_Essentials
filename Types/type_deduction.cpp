/*!
 *  \file       type_deduction.cpp
 *  \brief
 *
 */


#include "type_deduction.hpp"

#include <gtest/gtest.h>


/*!
 *  \note       使用{}初始化器类表可以尽可能减少意料之外的类型转换
 */
TEST(UTester4TypeDeduction, CheckDeduceTypeByInitializerList)
{
    char my_v1 = 12345;         // 12345的类型是int
    // char your_v1{12345};     // 错误： 窄化转换
    auto him_v1 = 12345;
    auto her_v1{12345};

    int my_v2 = 'c';        // 'c'的类型是char
    int your_v2{'c'};       // 正确： 隐式地char ---> int类型转换
    auto him_v2 = 'c';
    auto her_v2{'c'};

    using T = long;
    T my_v3 = getCppStandardNo();
    T your_v3{getCppStandardNo()};      /* 当且仅当getCppStandardNo()的类型能被隐式地转换成T时，该语句有效 */
    auto him_v3 = getCppStandardNo();
    auto her_v3{getCppStandardNo()};
}
