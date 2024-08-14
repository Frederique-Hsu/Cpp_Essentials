/*!
 *  \file       test_namespaces.c++
 *  \brief      Adopt the boost::test unit test framework to carry out the testing
 *              for current project.
 *  \author     Frederique Hsu
 *  \date       Sat.    22 June 2024
 *
 */


#include <boost/test/unit_test.hpp>


/*!
 *  \title      名字空间
 *
 *  \section    模块化
 *
 *  \details    任何实际问题都是由若干独立部分组成的。在C++中，函数和类提供了相对细粒度的关注点分离，
 *              库、源文件和编译单元则提供了粗粒度的分离。
 *
 *              逻辑上最理想的方式是模块化(modularity)，即独立的事物保持分离，只允许通过良好定义的接口
 *              访问“模块”。
 *              C++通过语言特性（如函数、类和名字空间）的组合和源码的组织来表达模块化。
 */


#include "utils.hpp"
#include "misc.hpp"

BOOST_AUTO_TEST_SUITE(UTest4Namespaces)

/*!
 *  \attention  一个名字空间形成一个作用域，通常的作用域规则也适用于名字空间。
 *              程序规模越大，用名字空间表达程序的逻辑划分就越有用。
 *              全局作用域也是一个名字空间，可以显式地用 :: 来引用。
 */

BOOST_AUTO_TEST_CASE(CheckHowCppNamespacesWork)
{
    g();
}

BOOST_AUTO_TEST_CASE(CheckTheUtilitySplit)
{
    const std::string sentence("to check the utility function split");
    std::vector<std::string> words = split(sentence);

    for (auto& word : words)
    {
        std::cout << word << std::endl;
    }
    BOOST_TEST_CHECK(words.size() == 6);
}

BOOST_AUTO_TEST_CASE(CheckNamespaceArgumentDependentLookup)
{
    auto fn = [](Chrono::Date d, std::string s) {
        if (d == s)
        {
            std::cout << "they are identical" << std::endl;
        }
        else if (d == "August 4, 2023")
        {
            // ...
        }
    };

    fn(Chrono::Date(2024, 06, 22), std::string("2024 06 22"));
}

namespace N
{
    struct S
    {
        int i;
    };

    void f(S) { std::cout << "called N::f(S)" << std::endl; }
    void g(S) { std::cout << "called N::g(S)" << std::endl; }
    void h(int) { std::cout << "called N::h(int)" << std::endl; }

    template<class T> void f(T, int)
    {
        std::cout << "called N::f<T>(T, int)" << std::endl;
    }

    class X
    {
    };
}

namespace N2
{
    N::X x;

    void f(N::X, unsigned)
    {
        std::cout << "called N2::f(N::X, unsigned)" << std::endl;
    }

    void g()
    {
        std::cout << "called N2::g()" << std::endl;

        /*!
         *  \note   此处的f(x, 1)看上去应该会去调用N2::f(N::X, unsigned)函数的。
         *          但实际上却去调用N::template<class T> void f(T, int)了。 为什么呢？
         *
         *  \attention  因为编译器会应用重载解析规则，并找到最佳匹配。
         *              对于f(x, 1)， N::f<T>(T, int)是最佳匹配。因为对于参数1, 类型int较unsigned更匹配。
         */
        f(x, 1);
    }
}

BOOST_AUTO_TEST_CASE(FunctionCallingLookupBetweenNamespaceAndClass)
{
    struct Base
    {
        void f(N::S) { std::cout << "called Base::f(N::S)" << std::endl; }
    };

    struct Derived : Base
    {
        void mfn(N::S) { std::cout << "called Derived::mfn(N::S)" << std::endl; }

        void g(N::S x)
        {
            /*!
             *  \note   当一个类成员调用命名函数时，编译器会优先选择同一个类的成员或其基类的，
             *          而不是基于参数类型找到的函数。
             */
            f(x);
            mfn(x);
            N::h(1);
        }
    };

    Derived obj;
    obj.g(N::S{1});

    N2::g();
}

/*!
 *  \note   名字空间是开放的。即，你可以从多个分离的名字空间声明中向一个名字空间添加成员。
 *          这样，名字空间的成员就不需要连续放置在单一的文件中。
 *          在编写代码时，推荐使用很多小的名字空间，而不是将大段的代码放入单一的名字空间。
 *          将一个名字空间的成员分散在多个分离的名字空间声明中还有另外一个原因：
 *          我们有时希望将名字空间作为接口的部分与用来支持简单实现的部分区分开来。
 */
namespace Mine
{
void mf() { std::cout << "called Mine::mf()" << std::endl; }
}

void yf() { std::cout << "called ::yf()" << std::endl; }

namespace Mine
{
void mg() { std::cout << "called Mine::mg()" << std::endl; }
}

BOOST_AUTO_TEST_CASE(CheckMultipleSmallNamespaceFunctionsGatheredIntoBigOne)
{
    Mine::mf();
    Mine::mg();

    yf();
}

BOOST_AUTO_TEST_SUITE_END()
