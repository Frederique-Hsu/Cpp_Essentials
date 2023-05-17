/*!
 *  \file       Array.cpp
 *  \brief
 *
 */


#include "Array.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <string>


TEST(UTester4Array, CheckAssignStringLiteral)
{
    char* p = "Plato";  /*! \warning    ISO C++ does not allow conversion from string literal to char* */
    // p[4] = 'e';     /*! \warning    字符串字面量的对象不能被修改 */

    /*!
     *  \note   如果希望字符创能被修改，最好把字符放在一个非常量的数组中
     */
    char str[] = "Zeno";
    str[0] = 'R';

    std::cout << "Beep at the end of message\a\n" << std::endl;

    /* 可以用空格把一条长字符串分割开以使程序文本显得整洁美观 */
    char alpha[] = "abcdefghijklmnopqrstuvwxyz\n"
                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::cout << alpha << std::endl;

    /*!
     *  \note   允许在字符串中间存在空字符，但是大多数程序都会忽略空字符之后的内容
     */
    char name[] = "Elon\000Musk";
    std::cout << "name = " << name << std::endl;
    EXPECT_EQ(std::strlen(name), 4);
}

TEST(UTester4Array, ExpressRawStringLiteral)
{
    using namespace std;
    /*!
     *  \note   在正则表达式中存在大量的反斜线(\)和双引号(")，这些字符需要转义。写太多的转义字符很容易出错。
     *          为解决这个问题，C++提供了原始字符串字面值常量raw string literal
     *          在原始字符串字面值常量中，反斜线就是反斜线，双引号就是双引号。
     *
     *  \remark 原始字符串字面值常量使用R"(ccc)"的形式表示字符序列ccc，开头的R用于把原始字符串字面值常量和普通的
     *          字符串字面值常量区别开来。一对括号的作用是允许我们使用非转义的双引号。
     */
    std::string regular_expression = R"(\w\\w)";
    cout << regular_expression << endl;

    string complex_regular_expression = R"***("quoted string containing the usual terminator ("))")***";
    cout << complex_regular_expression << endl;

    string counts{R"(1
                  22
                  333)"};
    cout << counts << endl;
}

TEST(UTester4Array, ExpressUnicodeLiteral)
{
    const wchar_t widestr[] = L"angst";     // 前缀是L的字符串是由宽字符组成的。
    EXPECT_TRUE(sizeof(wchar_t) == 4);
    EXPECT_EQ(sizeof(widestr), 4 * 6);
    std::wcout << widestr << std::endl;

    const wchar_t wide_raw_str[] = LR"(angst)";
    EXPECT_EQ(sizeof(wide_raw_str), sizeof(wchar_t) * 6);

    // std::wstring my_chinese_name{L"徐赞"};
    const wchar_t chinese_name[] = LR"(徐赞)";
    EXPECT_EQ(sizeof(chinese_name), 4 * 3);
    const wchar_t my_chinese_name[] = L"徐赞";
    std::wcout << my_chinese_name << std::endl;

    std::string name{"徐赞"};
    std::cout << name << std::endl;

    auto ordinary_str = "folder\\file";         // 基于ASCII字符集的字符串
    auto ordinary_raw_str = R"(folder\file)";;  // 基于ASCII字符集的原始字符串
    const char* utf8_str = u8"folder\\file";           // UTF-8字符串
    const char* utf8_raw_str = u8R"(folder\file)";     // UTF-8原始字符串
    const char16_t* utf16_str = u"folder\\file";           // UTF-16字符串
    const char16_t* utf16_raw_str = uR"(folder\file)";     // UTF-16原始字符串
    const char32_t* utf32_str = U"folder\\file";           // UTF-32字符串
    const char32_t* utf32_raw_str = UR"(folder\file)";     // UTF-32原始字符串

    std::cout << ordinary_str << "\t" << ordinary_raw_str << "\n"
              << utf8_str << "\t" << utf8_raw_str << "\n";
    std::wcout << utf16_str << "\t" << utf16_raw_str << "\n"
               << utf32_str << "\t" << utf32_raw_str << "\n"
               << std::endl;

    const char unicode_str[] = u8"The official vowels in Danish are: a e i o u, \u00E6, \u00F8, \u00E5 and y";
    std::cout << unicode_str << std::endl;
    std::cout << "strlen(unicode_str) = " << std::strlen(unicode_str) << std::endl;
    std::cout << "sizeof(unicode_str) = " << sizeof(unicode_str) << std::endl;

    auto Slavic_letter_a = "\u0430";
    auto Slavic_letter_utf8_a = u8"\uD0B0";
    auto Slavic_letter_utf16_a = u"\u0430";
    auto Slavic_letter_utf32_a = U"\u00000430";
    std::cout << Slavic_letter_a << "\t";
    std::cout << Slavic_letter_utf8_a << "\t";
    std::wcout << Slavic_letter_utf16_a << "\t";
    std::wcout << Slavic_letter_utf32_a << std::endl;
}

TEST(UTester4Array, PointerToArray)
{
    int v[] = {1, 2, 3, 4};
    int* p1 = v;        // 指向数组首元素的指针（隐式转换）
    int* p2 = &v[0];    // 指向数组首元素的指针
    int* p3 = v + 4;    // 指向数组尾后位置的指针
    int* p4 = v - 1;    // 首元素之前的位置是未定义的，应避免使用。
    int* p5 = v + 7;    // 尾元素之后的位置是未定义的，应该避免使用。

    using namespace std;
    cout << "p1 address = " << p1 << endl;
    cout << "p2 address = " << p2 << endl;
    cout << "p3 address = " << p3 << endl;
    cout << "p4 address = " << p4 << endl;
    cout << "p5 address = " << p5 << endl;

    /*!
     *  \warning    超出数组边界的地址可以读取，但是不能写入。
     *              而读取出来的也是无意义的。
     */
    cout << "*(p1 + 0) = " << *(p1 + 0) << endl;
    cout << "*(p1 + 1) = " << *(p1 + 1) << endl;
    cout << "*(p1 + 2) = " << *(p1 + 2) << endl;
    cout << "*(p1 + 3) = " << *(p1 + 3) << endl;
    cout << "*p3 = " << *p3 << endl;
    cout << "*p4 = " << *p4 << endl;
    cout << "*p5 = " << *p5 << endl;

    // *p5 = 10;   /* Error: stack smashing detected, terminated. */
}
