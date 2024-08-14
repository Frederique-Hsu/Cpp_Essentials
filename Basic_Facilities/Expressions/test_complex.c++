/*!
 *  \file       test_complex.c++
 *  \brief
 *
 */



#include <CppUTest/TestHarness.h>

#include "complex.hpp"

TEST_GROUP(UTester4Complex)
{
};

TEST(UTester4Complex, CheckConstExprConstructor)
{
    my::complex<double> object(3, 4);

    constexpr my::complex<double> z1{1, 2};
    constexpr double re = z1.getReal();
    CHECK_EQUAL(re, 1.0);
    constexpr double im = z1.getImag();
    CHECK_EQUAL(im, 2.0);

    constexpr my::complex<double> z2(re, im);
    CHECK_EQUAL(z2.getReal(), re);
    CHECK_EQUAL(z2.getImag(), im);

    constexpr my::complex<double> z3(z1);
    CHECK_EQUAL(z3.getReal(), z1.getReal());
    CHECK_EQUAL(z3.getImag(), z1.getImag());
}
