/*!
 *  \file       function_pointer.hpp
 *  \brief      Study the topic of function pointer
 *
 */


#pragma once

#include <string>
#include <vector>

/*!
 *  \title      函数指针
 *
 *  \details    与数据对象类似，由函数体生成的代码也置于某块内存区域中，因此它也有自己的地址。
 *              既然我们可以让指针指向对象，当然也就可以让指针指向函数。
 *
 *  \note       我们不允许函数指针修改它所指的代码，程序员只能对函数做两种操作：
 *              1. 调用它或者获取它的地址
 *              2. 通过获取函数地址得到的指针能被用来调用该函数
 */

namespace function_pointer
{
void error(std::string s);

/*!
 *  \note   普通函数在头文件里只能放置声明，不能放置函数实现。 函数实现要放到源文件里。
 *          否则在调用的时候，编译器会报告重复定义的错误。
 *          只有模板的声明和实现都是放在头文件里。
 */
void f1(std::string);
int f2(std::string);
void f3(int*);

void output(std::string s);
int accumulate(int*);
}


#define ALGORITHM_USE_FUNCTION_OBJECT       1
#define ALGORITHM_USE_FUNCTION_POINTER      2
#define ALGORITHM_ARGUMENT                  ALGORITHM_USE_FUNCTION_POINTER

#if (ALGORITHM_ARGUMENT == ALGORITHM_USE_FUNCTION_OBJECT)
    using CFT = int(const void*, const void*);
    /*!
     *  \remark     函数指针为算法的参数化提供了一种途径。因为C语言没有函数对象或者lambda表达式等机制，
     *              所以在C风格的代码中，经常把函数指针用作函数参数。
     */
    void shell_sort(void* base, size_t n, size_t sz, CFT cmp);
#elif (ALGORITHM_ARGUMENT == ALGORITHM_USE_FUNCTION_POINTER)
    void shell_sort(void* base, size_t n, size_t sz, int (*cmp)(const void*, const void*));
#endif

struct User
{
    const char* name;
    const char* id;
    int depth;
};

void print_id(std::vector<User>& v);

int cmp1(const void* p, const void* q);
int cmp2(const void* p, const void* q);
int cmp3(const User* p, const User* q);


/*!
 *  \note   我们可以将指向noexcept函数的指针声明成noexcept
 *          函数指针必须反映函数的链接信息，链接说明和noexcept都不能出现在类型别名中。
 */
void fn(int) noexcept;
void gc(int);
