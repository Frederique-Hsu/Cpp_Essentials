/*!
 *  \file       Object_LValue_RValue.cpp
 *  \brief      研究C++的对象， 左值与右值
 *
 */



#include <gtest/gtest.h>


/*!
 *  \note       什么是对象？
 *  \details    我们需要用一个名字来表示“内存中的某个东西”，这就是对象一词最简单和最基本的含义。\n
 *              对象（object）是指一块连续的存储区域。
 *
 *  \note       左值（lvalue）
 *  \details    左值是指向对象的一条表达式。“左值”的字面意思是“能用在赋值运算符左侧的东西”， \n
 *              但其实不是所有左值都能用在赋值运算符的左侧，左值也有可能指示某个常量。\n
 *              未被声明成const的左值称为可修改的左值(modifiable lvalue)
 *
 *  \note       右值（rvalue）
 *  \details    右值是指“不能作为左值的值”，比如像函数返回值一样的临时值
 *
 *
 */


/*================================================================================================*/


/*!
 *  \note       对象的声明周期 lifetime
 *  \details    对象的声明周期从对象的构造函数完成的那一刻开始，直到析构函数执行为止。
 *
 *
 *  \list
 *              1. 自动(automatic)对象, 在大多数实现中，自动对象被分配在栈空间上。每调用一次函数，获取新的栈帧
 *                 stack frame以存放它的自动对象。
 *
 *              2. 静态(static)对象，在全局作用域或名字空间作用域中声明的对象以及在函数中声明的static成员只被创建
 *                 并初始化一次，并且直到程序结束之前都“活着”。静态对象在程序的整个执行周期内地址唯一。
 *
 *              3. 自由存储(free store)对象， 用new和delete直接控制其生命周期的对象
 *
 *              4. 临时(temporary)对象， 计算的中间结果或用于存放const实参引用的值的对象。
 *
 *              5. 线程局部(thread-local)对象，声明为thread_local的对象，这样的对象随着线程的创建而创建，随着
 *                 线程的销毁而销毁。
 *  \endlist
 */



/*================================================================================================*/

/*!
 *  \brief      类型别名
 */

using PChar = char*;                // 字符创指针
using FnPtr = int(*)(double);       // 函数指针，该函数接受一个double, 且返回一个int

using Char = char;
// using UChar = unsigned Char;
using UChar = unsigned char;

typedef int     int32_t;        // 等价于  using int32_t = int;
typedef short   int16_t;        // 等价于  using int16_t = short;
typedef void(*PtoF)(int);       // 等价于  using PtoF = void(*)(int);

template<typename T>
using Vector = std::vector<T, std::allocator<T>>;       // using可用于引入一个template别名
