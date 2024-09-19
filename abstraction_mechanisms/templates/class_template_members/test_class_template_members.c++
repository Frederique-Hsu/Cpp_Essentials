/*!
 *  \file       test_class_template_members.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "template_alias.hpp"

TEST(UTest4TemplateMembers, CheckMemberTypeAlias)
{
    Vector<int> numbers(std::initializer_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    
    for (Vector<int>::iterator iter = numbers.begin(); iter != numbers.end(); ++iter)
    {
        std::cout << *iter << "  ";
    }
    std::cout << std::endl;
    for (auto index = 0U; index < numbers.size(); ++index)
    {
        std::cout << numbers[index] << "  ";
    }
    std::cout << std::endl;
    
    for (auto number : numbers)
    {
        std::cout << number << ",  ";
    }
    std::cout << std::endl;
    
    EXPECT_EQ(numbers.front(), 1);
    EXPECT_EQ(numbers.back(), 10);
}

TEST(UTest4TemplateMembers, CheckVectorPushBackAndPopBack)
{
    Vector<int> numbers(4);
    EXPECT_EQ(numbers.size(), 4);
    EXPECT_EQ(numbers.capacity(), 2 * 4);
    
    auto index = 0U;
    for (index = 0U; index < numbers.size(); ++index)
    {
        numbers.at(index) = index;
    }
    auto capacity = numbers.capacity();
    for (index = numbers.size(); index < capacity + 2; ++index)
    {
        numbers.push_back(index);
    }
    EXPECT_EQ(numbers.size(), 10);
    EXPECT_EQ(numbers.capacity(), 16);
    for (auto citer = numbers.cbegin(); citer != numbers.end(); ++citer)
    {
        std::cout << *citer << ",  ";
    }
    std::cout << std::endl;
    
    numbers.pop_back();
    EXPECT_EQ(numbers.size(), 10 - 1);
}

struct Point
{
    int x_coord;
    int y_coord;
};

template<typename T>
struct X
{
    // static const Point point{100, 250}; // Error: 'constexpr' needed for in-class initialization of static data member
    static constexpr Point point{100, 250};
    static const int m1 = 7;
    // static int m2 = 8;      // Error: ISO C++ forbids in-class initialization of non-const static member of class template
    static int m3;
    
    static void f1() { /* ... */ }
    static void f2();
};

// template<typename T> int X<T>::m1 = 8;      // Error: m1 has 2 initializer
template<typename T> int X<T>::m3 = 99;

template<typename T>
void X<T>::f2()
{
}

template<typename T>
struct Dummy
{
    static int a;
    static int b;
};

template<typename T> int Dummy<T>::a = 25;

TEST(UTest4TemplateMembers, CheckStaticMember)
{
    int* pa = &Dummy<int>::a;   // 一个static成员只有真被使用时才需要定义， 如a,  因为b未使用，可以不用在类外定义。
    EXPECT_EQ(*pa, 25);
}

template<typename T>
struct Inside
{
    enum E1
    {
        a,
        b
    };
    // enum E2;    // Error: 基础类型未知
    enum class E3;
    enum E4 : char;
    
    struct C1
    {
        int a;
        float b;
    };
    struct C2;
};

template<typename T>
enum class Inside<T>::E3
{
    Yes,
    No
};

template<typename T>
enum Inside<T>::E4 : char
{
    X,
    Y
};

template<typename T>
struct Inside<T>::C2
{
    void*   pointer[4];
    int     (*fnptr)(int& a, int& b);
};