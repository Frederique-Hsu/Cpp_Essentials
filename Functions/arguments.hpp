/*!
 *  \file       arguments.hpp
 *  \brief
 *
 */


#pragma once


/*!
 *  \note   调用函数时，为函数的形参（formal argument, 即：parameters）申请内存空间，
 *          并用实参（actual arguments，简称：arguments）初始化对应的形参.
 *
 *          参数传递的语义与初始化的语义一致， 即：拷贝初始化。
 *          编译器负责检查实参的类型是否与对应的形参类型吻合，并在必要的时候执行标准类型转换或者
 *          用户自定义的类型转换。
 *          除非形参是引用，其他情况下传入函数的是实参的副本。
 */


/*!
 *  \section1        Prototypes
 */

int* find(int* first, int* last, int v);

/*!
 *  \endsection1
 */
