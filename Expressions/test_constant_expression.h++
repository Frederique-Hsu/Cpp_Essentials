/*!
 *  \file       test_constant_expression.h++
 *  \brief
 *
 */


#pragma once

#include <CppUTest/TestHarness.h>

/*!
 *  \note   C++提供了两种与“常量”有关的概念：
 *
 *          1. constexpr: 编译时求值，其作用是器用并确保编译时求值
 *          2. const: 在作用域内不改变其值
 *
 *  \remark 常量表达式(constant expression)是指由编译器求值的表达式。它不能包含任何编译时未知的值，
 *          也不能具有其他副作用。
 */

TEST_GROUP(UTester4ConstExpr)
{
};

