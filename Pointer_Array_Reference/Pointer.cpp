/*!
 *  \file       Pointer.cpp
 *  \brief      研究C++的指针
 *
 */


#include <gtest/gtest.h>

void accessVoidPointer(int* pint)
{
    void* pvoid = pint;     // Okay: 发生了从int*到void*的隐式类型转换
    // *pvoid;     // Error: 不允许解引用void*
    // ++pvoid;    // Error: 不允许对void*执行递增操作，因为所指的对象尺寸未知。

    int* pint2 = static_cast<int*>(pvoid);  // 显式转换回int*

    // double* pdbl1 = pvoid;      // Error
    // double* pdbl2 = pint;       // Error
    double* pdbl3 = static_cast<double*>(pvoid);    // 不安全

    /*!
     *  \warning    在原来的C语言代码中，很多人习惯于定义一个宏NULL来表示空指针。
     *              然而，在不同的具体实现中NULL的定义有所差别； 例如，NULL可能是0，也可能是0L.
     *              在C语言中，NULL通常是(void*)0，这种用法在C++中是非法的。
     *
    #define NULL    ((void*)0)
    int* p = NULL;      // Cannot initialize a variable of type 'int' with an rvalue of type void*
     */
}

TEST(UTester4Pointer, CheckDeferencing)
{
    char c = 'a';
    char* p = &c;   // 取地址运算符 &c
    char c2 = *p;   // 解引用运算符 *p

    EXPECT_EQ(c2, 'a');
}

TEST(UTester4Pointer, PointerCategories)
{
    int* pi;        // 指向int的指针
    char** ppc;     // 指向字符指针的指针
    int* ap[15];    // ap是一个数组，包含15个指向int的指针
    int (*fp)(char*);       // 指向函数的指针，该函数接受一个char*实参，返回一个int
    int* f(char*);          // 该函数接受一个char*实参，返回一个指向int的指针

    EXPECT_EQ(sizeof(pi), 8);
    EXPECT_EQ(sizeof(ppc), 8);
    EXPECT_EQ(sizeof(ap), 8 * 15);
    EXPECT_EQ(sizeof(fp), 8);
    EXPECT_EQ(sizeof(f("function")), 8);
}

TEST(UTester4Pointer, CheckConstPointer)
{
    char name[] = "Bjarne Stroustrup";
    const char* alias = "The father of C++";

    const char* pname = name;       // 指向常量的指针, 指向的变量name不可修改
    // pname[3] = 'g';              /* 错误： 常量不可修改 */
    pname = alias;                  // 但指针可以转移，指向别的变量

    char* const constptr = name;    // 常量指针，指针不可更改
    constptr[3] = 'h';              // 指向的变量可以更改
    // constptr = alias;            // 错误： 指针constptr是一个常量，不可更改

    const char* const cpc = name;   // 指向常量的常量指针
    // cpc[3] = 'h';                   // 错误: cpc指向常量，不可更改
    // cpc = alias;                    // 错误： 指针cpc本身就是一个常量

    char* const cp = "const";     // 指向char的常量指针
    char const* pc = "const";     // 指向常量const的指针
    const char* pc2 = "const";    // 指向常量char的指针
}

TEST(UTester4Pointer, ConstPointerCannotAssignNormalPointer)
{
    int a = 1;
    const int c = 2;
    const int* p1 = &c;
    const int* p2 = &a;

    // int* p3 = &c;   // 错误： 用const int*初始化int*
    // *p3 = 7;        // 并试图改变常量c的值
}
