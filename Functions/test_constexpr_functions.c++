/*!
 *  \file       test_constexpr_functions.c++
 *  \brief      Implement the \a UTest4ConstexprFunction class and perform the unit test.
 *
 */


#include "test_constexpr_functions.h++"

#include "constexpr_functions.hpp"

TEST(UTest4ConstexprFunction, CheckConstexprFunctionCanBeEvaluatedOnCompileTime)
{
    /*!
     *  \note   当constexpr出现在函数定义中时，它的含义是“如果给定了常量表达式作为实参，则该函数应该能用在常量表达式中”，
     *          而当constexpr出现在对象定义中时，它的含义时“在编译时对初始化器求值”。
     */
    constexpr int f9 = factorial(9);    // 必须在编译时求值

    EXPECT_EQ(typeid(f9), typeid(int)) << "f9 = " << f9;

    auto fnct = [](int n) {
        int f5 = factorial(5);      // 可能在编译时求值
        int fn = factorial(n);      // 在运行时求值(n是变量)

        constexpr int f6 = factorial(6);    // 必须在编译时求值
        // constexpr int fnn = factorial(n);   // 错误: 无法确保在编译时求值（因为n是变量）

        char array[factorial(4)];       // OK: 数组的尺寸必须是常量，而factorial()恰好是constexpr
        // char array2[factorial(n)];      // 错误：数组的尺寸必须是常量，而n是变量，无法确保factorial(n)在编译时求值
    };

    fnct(8);
}


/*!
 *  \section    constexpr and ref.
 *
 *  \warning    constexpr函数不允许有副作用，因此我们不能向非局部对象写入内容。
 */
constexpr int UTest4ConstexprAndReference::fib(int n)
{
    return ( static_cast<std::size_t>(n) < sizeof(fib_list)/sizeof(fib_list[0]))
               ? fib_list[n]
               : fib(n-1) + fib(n-2);
}

TEST_F(UTest4ConstexprAndReference, CheckHowConstexprAndRefWorked)
{
    EXPECT_EQ(fib(5), 8);
    EXPECT_EQ(fib(10), 89);

    /*!
     *  \note   constexpr函数可以接受引用实参，尽管它不能通过这些引用写入内容。
     */
    constexpr my::complex<float> z(2.0);

    const my::complex<double> dcomp(double{3.0}, double{4.0});
}

TEST_F(UTest4ConstexprAndReference, CheckConstexprFunctionReturnPointer)
{
    static const int x = 5;
    constexpr const int* p1 = my::addr(x);
    constexpr int xx = *p1;
    EXPECT_EQ(xx, 5);

    static int y;
    constexpr const int* p2 = my::addr(y);
    // constexpr int yy = *p2;      // 错误： 试图读取一个变量的值

    // constexpr const int* tp = my::addr(5);      // 错误： addr是要读取一个变量的地址，若使用常量表达式反而无法读取。
}

constexpr int low = 0;
constexpr int high = 99;

constexpr int check(int i)
{
    return (low <= i && i < high) ? i : throw std::out_of_range("Out of the range");
}

TEST_F(UTest4ConstexprAndReference, CheckConstexprConditionalEvaluate)
{
    auto sum = [](int x, int y, int z) {
        return x + y + z;
    };

    /*!
     *  \note   constexpr函数之外的表达式不会在编译时求值，如此处的sum(3, 4, 5)不会在编译时求值。
     *          在这种情况下，constexpr函数可以请求运行时求值。
     */
    constexpr int val = check(sum(3, 4, 5));
    EXPECT_EQ(val, 12);

#if false
    EXPECT_THROW({
        constexpr int val = check(sum(123, 456, 789));
    }, std::out_of_range);
#endif
}
