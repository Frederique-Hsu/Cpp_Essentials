/*!
 *  \file       function_arguments.hpp
 *  \brief
 *
 */


#pragma once

#include <vector>


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

namespace my
{
    int strlen(const char*);
    char* strcpy(char* to, const char* from);
    int strcmp(const char*, const char*);
}

float fsqrt(const float& val);
void update(float& val);

/*!
 *  \remarks    引用传递
 *
 *  \details    引用传递的准确描述应该是左值引用传递，原因是函数不能接受一个右值引用作为它的参数。
 *
 *              右值能绑定到右值引用上，但不能绑定到左值引用上。
 *              左值能绑定到左值引用上，但不能绑定到右值引用上。
 */
void fnref(std::vector<int>&);          // 非const左值引用参数
void fnref(const std::vector<int>&);    // const左值引用参数
void fnref(std::vector<int>&&);         // 右值引用参数

/*!
 *  \section    如何选择参数的传递方式?
 *
 *  \list
 *      \li     对于小对象使用值传递的方式
 *      \li     对于你无需修改的大对象，使用const引用传递
 *      \li     如果需要返回计算结果，最好使用return而非通过参数修改对象
 *      \li     使用右值引用实现移动和转发
 *      \li     如果找不到合适的对象，则传递指针（用nullptr表示“没有对象”）
 *      \li     除非万不得已，否则不要使用引用传递。 即：当我们需要修改对象的值时，传递指针比使用引用更容易表达清楚程序的原意。
 *  \endlist
 */

/*!
 *  \endsection1
 */
