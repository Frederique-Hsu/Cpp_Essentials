/*!
 *  \file       array_arguments.hpp
 *  \brief
 *
 */


#pragma once

#include <iostream>

void odd(int* p);
void odd(int a[]);
void odd(int buf[1020]);

/*!
 *  \section    数组参数
 *
 *  \details    当数组作为函数的参数时，实际传入的是指向该数组首元素的指针。
 *              对于被调用函数来说，数组的尺寸是不可见的。这是很多错误的根源。
 *              对于数组参数，可以再传入一个参数，用它来表示数组的大小。如下第一个compute函数。
 *
 *              不过这么做顶多算一种变通的方法，更好的做法是传入某些容器。
 *
 *              如果确实想传入一个数组而非容器，或者指向数组首元素的指针，你可以把参数的类型声明为数组的引用。
 *              如下第二个compute函数
 *              对于数组引用类型的参数来说，元素个数也是其类型的一部分。因此，数组引用的灵活性远不如指针或容器。
 *
 *              通常只在模板中才会使用数组引用，此时元素的个数可以通过推断得到。 如下第三个compute函数模板
 *
 */
void compute(int* vec_ptr, int vec_size);
void compute(int (&r)[4]);
template<class T, int N> void compute(T (&r)[N]);


/*================================================================================================*/

template<class T, int N> void compute(T (&r)[N])
{
#define stringify(a) #a

    std::cout << "Type is " << stringify(T) << std::endl;
    std::cout << "N = " << N << std::endl;

    T sum = T{};
    for (int index = 0; index  <N; ++index)
    {
        sum += r[index];
    }
    std::cout << "sum3 = " << sum << std::endl;
}
