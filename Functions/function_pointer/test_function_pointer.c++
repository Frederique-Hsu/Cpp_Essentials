/*!
 *  \file       test_function_pointer.c++
 *  \brief
 *
 */


#include "function_pointer.hpp"

#include <gtest/gtest.h>
#include <cstdlib>
#include <algorithm>

TEST(UTest4FunctionPointer, CheckFunctionPointerBasicUsage)
{
    void (*efct)(std::string);

    auto fnptr = [&efct]() -> void {
        efct = &function_pointer::error;    // 指向函数的指针，该函数接受一个字符串参数，不返回任何东西
        efct("error");
    };
    fnptr();

    /*!
     *  \remark     解引用函数指针时可以用*，也可以不同。
     *              同样，获取函数地址时可以用&，也可以不用。
     */
    void (*f1)(std::string) = &function_pointer::error;
    void (*f2)(std::string) = function_pointer::error;

    f1("Vanessa");
    (*f2)("Mary Rose");

    /*============================================================================================*/

    void (*pf)(std::string);    // 函数指针是对象，不能放在头文件里，只能在源文件里。

    /*!
     *  \note   函数指针进行赋值操作时，要求完整的函数类型都必须精确匹配，返回类型和参数列表必须完全相同。
     */
    pf = &function_pointer::f1;
    // pf = &function_pointer::f2;      // Error: 返回类型错误
    // pf = &function_pointer::f3;      // Error: 参数类型错误

    pf("Hera");
    // pf(1);       // Error: 参数类型错误
    // int i = pf("Zeus");      // Error: 试图把void赋给int
}

TEST(UTest4FunctionPointer, CheckFunctionPointerConversion)
{
    using P1 = int (*)(int*);
    using P2 = void (*)(void);

#if false
    auto output = [](std::string s) -> void {
        std::cout << s << std::endl;
    };
    P2 pf2 = reinterpret_cast<P2>(output);  // 不能将lambda函数转换为函数指针。
#endif

    /*!
     *  \warning    C++允许把一个函数指针转换成别的函数指针，但之后必须把得到的结果指针转换回原来的类型，否则就会
     *              出现意想不到的错误。
     */
    auto fn = [](P1 pf) {
        P2 pf2 = reinterpret_cast<P2>(pf);  // 函数指针之间的转换只能使用reinterpret_cast， 因为他们之间没有关联
        pf2();  // 可能发生严重错误

        P1 pf1 = reinterpret_cast<P1>(pf2);     // 把pf2再转换回来
        int x = 7;
        int y = pf1(&x);    // 此时执行是正常的。
        return y;
    };

    auto result = fn(&function_pointer::accumulate);
    EXPECT_EQ(result, 7);
}

TEST(Test4FunctionPointer, CheckSortAlgorithm)
{
    GTEST_SKIP();
    std::vector<User> heads = {{"Ritchie D.M.",     "dmr",  11271},
                               {"Sethi R.",         "ravi", 11272},
                               {"Szymanski T.G.",   "tgs",  11273},
                               {"Schryer N.L.",     "nls",  11274},
                               {"Schryer N.L.",     "nls",  11275},
                               {"Kernighan B.W.",   "bwk",  11276}};

    std::cout << "Heads in alphabetical order: " << std::endl;
    std::qsort(&heads, heads.size(), sizeof(User), cmp1);

    print_id(heads);

    std::cout << "Heads in order of department number: " << std::endl;
    std::qsort(&heads, heads.size(), sizeof(User), cmp2);
}

TEST(Test4FunctionPointer, CheckStandardQSortAlgorithm)
{
    std::vector<User> heads = {{"Ritchie D.M.",     "dmr",  11271},
                               {"Sethi R.",         "ravi", 11272},
                               {"Szymanski T.G.",   "tgs",  11273},
                               {"Schryer N.L.",     "nls",  11274},
                               {"Schryer N.L.",     "nls",  11275},
                               {"Kernighan B.W.",   "bwk",  11276}};

    std::cout << "Heads in alphabetical order: " << std::endl;
    std::sort(heads.begin(), heads.end(), [](const User& a, const User& b) { return a.name < b.name; });
    print_id(heads);

    std::cout << "Heads in order of department number: " << std::endl;
    std::sort(heads.begin(), heads.end(), [](const User& a, const User& b) { return a.depth < b.depth; });
    print_id(heads);
}

TEST(Test4FunctionPointer, CheckFunctionPointer_noexcept_and_linkinfo)
{
    void (*p1)(int) = fn;               // OK: 但是丢失了有用信息
    void (*p2)(int) noexcept = fn;      // OK: 保留了noexcept信息
    // void (*p3)(int) noexcept = gc;      // Error: 原函数gc并不确定会抛出异常.

    using Pn = void(int) noexcept;
    // using Pc = extern "C" void(int);
}
