/*!
 *  \file       Array_Utils.cpp
 *  \brief      探寻数组的更多实用方法
 *
 */


#include <gtest/gtest.h>
#include <string.h>
#include <iostream>

#include "Array.hpp"

// extern "C" int strlen(const char*);

TEST(UTester4ArrayPointer, CheckConversionBetweenArrayAndPointer)
{
    using namespace std;

    char v[] = "Annemarie";
    char* p = v;        /* char[] 到 char* 的隐式类型转换 */
    cout << "strlen(p) = " << strlen(p) << endl;
    cout << "strlen(v) = " << strlen(v) << endl;    /* char[] 到 char* 隐式类型转换 */

    // v = p;      /* 错误： 不允许给数组直接赋值 */
}

void fi(char v[])
{
    for (int i = 0; v[i] != 0; ++i)
    {
        std::cout << v[i] << ", ";
    }
    std::cout << std::endl;
}

void fp(char v[])
{
    for (char* p = v; *p != 0; ++p)
    {
        std::cout << *p << ", ";
    }
    std::cout << std::endl;
}

TEST(UTester4ArrayPointer, CheckArrayRoaming)
{
    char name[] = "Frederique Hsu";

    int index = 3;
    EXPECT_TRUE(name[index] == *(&name[0] + index));
    EXPECT_TRUE(name[index] == *(name + index));
    EXPECT_TRUE(name[index] == *(index + name));
    EXPECT_TRUE(name[index] == index[name]);

    /*!
     *  \note   对于内置数组array和数组之内的索引index， 有下式成立：
     *          array[index] == *(&array[0] + index) == *(array + index) == *(index + array) == index[array]
     */
}

TEST(UTester4ArrayPointer, CheckDistanceBetweenAdjacentArrayPointers)
{
    int vi[10];
    short vs[10];

    using namespace std;
    cout << vi << '\t' << &vi[1] << '\t' << &vi[1] - &vi[0] << '\t' << byte_diff(&vi[0], &vi[1]) << " bytes" << endl;
    cout << vs << "\t" << &vs[1] << "\t" << &vs[1] - &vs[0] << "\t" << byte_diff(&vs[0], &vs[1]) << " bytes" << endl;

    int v1[10];
    int v2[10];

    int valid_pointer_distance = &v1[5] - &v1[3];
    cout << "valid_pointer_distance = " << valid_pointer_distance << endl;
    int invalid_pointer_distance = &v1[5] - &v2[3];     // 结果是未定义的
    cout << "invalid_pointer_distance = " << invalid_pointer_distance << endl;

    int* valid_pointer = v2 + 2;
    int* invalid_pointer = v2 - 2;      // 该指针是未定义的，不合理的指针赋值

    cout << "v2 address = " << v2 << "\t" << "valid_pointer = " << valid_pointer << endl;
    cout << "invalid_pointer = " << invalid_pointer << endl;
}

void traverseArray(char array[], int size)
{
    for (int i = 0; i != size; ++i)
    {
        access(array[i]);       /* 祈祷数组array至少包含size个元素，否则就会越界 */
    }
#if 0
    for (char elem : array)      /* 错误： range-for-loop对指针无效 */
    {
        access(elem);
    }
#endif

    const int N = 10;
    char str[N];
    for (int i = 0; i != N; ++i)
    {
        access(str[i]);
    }
    for (char elem : str)       /* 正确： 当已知数组的大小时，可以使用range-for-loop */
    {
        access(elem);
    }
}

/* 传递数组 =======================================================================================*/

void print_m35(int matrix[3][5])
{
    for (int r = 0; r != 3; ++r)
    {
        for (int c = 0; c != 5; ++c)
        {
            std::cout << matrix[r][c] << "\t";
        }
        std::cout << std::endl;
    }
}

void print_mi5(int matrix[][5], int row)    /* 可以把矩阵（二维数组）的列维度当成实参传入函数 */
{
    for (int r = 0; r != row; ++r)
    {
        for (int c = 0; c != 5; ++c)
        {
            std::cout << matrix[r][c] << "\t";
        }
        std::cout << std::endl;
    }
}

// void print_mij(int matrix[][], int row, int column)     // 二维数组的第二个维度必须是已知的
void print_mij(int* matrix, int row, int column)
{
    for (int r = 0; r != row; ++r)
    {
        for (int c = 0; c != column; ++c)
        {
            // std::cout << matrix[r][c] << "\t";
            std::cout << matrix[r * column + c] << "\t";
        }
        std::cout << std::endl;
    }
}

TEST(UTester4ArrayPointer, PassArrayPointerToFunctionArgument)
{
    int matrix[3][5] = { { 1,  2,  3,  4,  5},
                         { 6,  7,  8,  9, 10},
                        {11, 12, 13, 14, 15} };
    print_m35(matrix);
    std::cout << "\n" << std::endl;
    print_mi5(matrix, 3);
    std::cout << "\n" << std::endl;
    print_mij(&matrix[0][0], 3, 5);
}
