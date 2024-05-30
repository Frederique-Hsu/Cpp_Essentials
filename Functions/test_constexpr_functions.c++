/*!
 *  \file       test_constexpr_functions.c++
 *  \brief      Implement the \a UTest4ConstexprFunction class and perform the unit test.
 *
 */


#include "test_constexpr_functions.h++"
#include "functions.hpp"

#include <complex>
#include <stdexcept>

/*!
 *  \brief  constexpr function.
 *  \note
 *  \list
 *      \li When \a constexpr is used in a function definition,
 *          it means "should be usable in a constant expression when given constant expressions
 *          as arguments."
 *
 *      \li When used in an object definition, it means "evaluate the initializer at compile time."
 *  \endlist
 *
 *  \warning    To be evaluated at compile time, a function must be suitably simple:
 *              1. a \a constexpr function must consist of a single return-statement;
 *              2. no loops and no local variables are allowed.
 *
 */
constexpr int factorial(int n)
{
    return (n > 1) ? n * factorial(n-1) : 1;
}

void UTest4ConstexprFunction::fn(int n)
{
    int f5 = factorial(5);  // may be evaluated at compile time.
    EXPECT_EQ(f5, fac(5));

    int fnValue = factorial(n);     // evaluated at run time (because n is a variable)
    EXPECT_EQ(fnValue, fac(n));

    constexpr int f6 = factorial(6);    // must be evaluated at compile time.
    EXPECT_EQ(f6, fac(6));

    // constexpr int fnn = factorial(n);   // error: cannot guarantee compile-time evaluation (n is a variable)

    char a[factorial(4)];   // OK: array bounds must be constant and factorial(4) is constexpr
    EXPECT_EQ(sizeof(a), factorial(4));

    char a2[factorial(n)];  // OK: array bounds must be constant, although n is a variable.
    EXPECT_EQ(sizeof(a2), factorial(n));
}

/*================================================================================================*/

int glob;

/*!
 *  \warning    a constexpr function may not have side effects.
 *              That is, a constexpr function is pure function.
 */
constexpr void bad_constexpr_func_1(int a)    // error: constexpr function cannot be void
{
    glob = a;   // error: side effect in a constexpr function.
}

constexpr int bad_constexpr_func_2(int a)
{
    if (a >= 0)     // error: if-statement in constexpr function
        return a;
    else
        return -a;
}

constexpr int bad_constexpr_func_3(int a)
{
    size_t sum = 0;                 // error: local variable in constexpr function
    for (int i = 0; i < a; ++i)     // error: loop in constexpr function
    {
        sum += factorial(i);
    }
    return sum;
}

/*================================================================================================*/

TEST_F(UTest4ConstexprFunction, CheckWhetherConstexprFunctionIsEvaluatedAtCompileTime)
{
    constexpr int f9 = factorial(9);    // must be evaluated at compile time
    EXPECT_EQ(f9, fac(9));
}

TEST_F(UTest4ConstexprFunction, ValidateWhenFunctionIsEvaluatedAtCompileTime)
{
    int n = 10;
    fn(n);
}

/*================================================================================================*/

constexpr int ftbl[] {1, 2, 3, 5, 8, 13};

constexpr int fib(int n)
{
    return (n < sizeof(ftbl) / sizeof(*ftbl)) ? ftbl[n] : fib(n-1) + fib(n-2);
}

/*!
 *  \note   It is possible for a constexpr function to return a reference or a pointer.
 */
constexpr const int* addr(const int& r)
{
    return &r;
}

TEST_F(UTest4ConstexprFunction, Check_constexpr_and_reference)
{
    EXPECT_EQ(fib(3), 5);
    EXPECT_EQ(fib(5), 13);
    EXPECT_EQ(fib(6), 21);
    EXPECT_EQ(fib(7), 34);

    constexpr std::complex<float> z{2.0};
    EXPECT_DOUBLE_EQ(z.real(), 2.0);

    /*========================================================*/

    static const int x = 5;
    constexpr const int* p1 = addr(x);
    constexpr int xx = *p1;
    EXPECT_EQ(xx, 5);

    static int y;
    constexpr const int* p2 = addr(y);
    // constexpr int yy = *p2;     // error: attempt to read a variable
    EXPECT_EQ(&y, p2);
    // constexpr const int* tp = addr(5);  // error: constexpr variable 'tp' must be initialized by a constant expression.
}

constexpr int low = 0;
constexpr int high = 99;

constexpr int check(int i)
{
    return ((low <= i) && (i < high)) ? i : throw std::out_of_range("out of range");
}

TEST_F(UTest4ConstexprFunction, Check_conditional_evaluation)
{
    auto fn = [](int x, int y, int z)
    {
        return x + y + z;
    };

    constexpr int value = check(fn(1, 2, 3));
    EXPECT_EQ(value, 6);

    EXPECT_THROW(check(fn(101, 102, 103)), std::out_of_range);
}
