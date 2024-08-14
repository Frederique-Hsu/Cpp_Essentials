/*!
 *  \file       function_pointer.cpp
 *  \brief
 *
 */


#include "function_pointer.hpp"

#include <iostream>
#include <cstring>

namespace function_pointer
{
void error(std::string s)
{
    std::cerr << "Error: " << s << std::endl;
}

void f1(std::string) {}
int f2(std::string) {}
void f3(int*) {}

void output(std::string s)
{
    std::cout << s << std::endl;
}

int accumulate(int* p)
{
    return int{} + *p;
}
}

/*!
 *  \brief      希尔排序
 *  \param      cmp - 使用cmp所指的比较函数把向量base的n个元素按照升序排列
 *  \param      sz - 元素的大小
 *  \param      base - 所指向的向量或数组
 */
#if (ALGORITHM_ARGUMENT == ALGORITHM_USE_FUNCTION_OBJECT)
void shell_sort(void* base, size_t n, size_t sz, CFT cmp)
#elif (ALGORITHM_ARGUMENT == ALGORITHM_USE_FUNCTION_POINTER)
void shell_sort(void* base, size_t n, size_t sz, int (*cmp)(const void*, const void*))
#endif
{
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i != n; ++i)
        {
            for (int j = i - gap; j >= 0; j -= gap)
            {
                char* b = static_cast<char*>(base);
                char* pj = b + j * sz;
                char* pjg = b + (j + gap) * sz;
                if (cmp(pjg, pj) < 0)
                {
                    for (int k = 0; k != sz; ++k)
                    {
                        char temp = pj[k];
                        pj[k] = pjg[k];
                        pjg[k] = temp;
                    }
                }
            }
        }
    }
}


void print_id(std::vector<User>& vec)
{
    for (auto& elem : vec)
    {
        std::cout << elem.name << "\t" << elem.id << "\t" << elem.depth << std::endl;
    }
}

/*!
 *  \warning    当对函数指针进行赋值或者初始化操作时，不会进行参数类型或返回类型的隐式转换，因此从cmp1, cmp2必须
 *              进行强制类型转换。
 */
int cmp1(const void* p, const void* q)
{
    return std::strcmp(static_cast<const User*>(p)->name,
                       static_cast<const User*>(q)->name);
}

int cmp2(const void* p, const void* q)
{
    return static_cast<const User*>(p)->depth - static_cast<const User*>(q)->depth;
}

int cmp3(const User* p, const User* q)
{
    return std::strcmp(p->id, q->id);
}
