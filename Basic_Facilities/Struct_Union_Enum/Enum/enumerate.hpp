/*!
 *  \file       enumerate.hpp
 *  \brief
 *
 */


#pragma once

#include <cstdint>

/*!
 *  \remark     enum class是一种限定了作用域的强类型枚举，它的枚举值位于enum的局部作用域内，枚举值不会隐式
 *              地转换成其他类型
 */
enum class Color
{
    red,
    green,
    blue
};

enum class Traffic_light
{
    red,
    yellow,
    green
};

enum Traffic_light_e    /* 普通的enum */
{
    red,
    yellow,
    green
};

enum class Warning : char  /* 火警等级 */
{
    green,
    yellow,
    orange,
    red
};

/*!
 *  \warning    普通的enum的枚举值位于enum本身所在的作用域中，它们隐式地转换成某些整数类型的值。
 *              所以，不能重复定义枚举值的名字。
 *
enum Warning_e
{
    green,
    yellow,
    orange,
    red
};
 */

void process(Warning key);

/*================================================================================================*/

enum class Printer_flags : std::uint8_t
{
    /*! \note   可用整型常量表达式初始化枚举值 */
    null            = 0b0000'0000,
    acknowledge     = 0b0000'0001,      /* 以二进制形式表示，更直观。 */
    paper_empty     = 0b0000'0010,
    busy            = 0b0000'0100,
    out_of_black    = 0b0000'1000,
    out_of_color    = 0b0001'0000,
};

constexpr Printer_flags operator|(Printer_flags a, Printer_flags b);
constexpr Printer_flags operator&(Printer_flags a, Printer_flags b);
void try_to_print(Printer_flags x);

/*================================================================================================*/

enum class Color_code : char;   /* C++允许先声明一个enum class, 稍后再给出它的定义 */
void foobar(Color_code* p);
