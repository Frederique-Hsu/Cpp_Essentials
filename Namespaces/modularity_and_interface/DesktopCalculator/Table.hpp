/*!
 *  \file       Table.hpp
 *  \brief
 *
 */


#pragma once


#include <map>
#include <string>

namespace Table
{
    /*!
     *  \attention  当需要把变量或对象放在头文件中时，为避免头文件被多个源文件包含而导致变量或对象重复定义，
     *              则需要将变量或对象加上extern修饰。extern表示该变量仅是声明，而不是定义。
     *
     *              extern修饰的变量或对象不能使用 =  因为"="即表示定义该变量。
     */
    extern std::map<std::string, double> table;
}
