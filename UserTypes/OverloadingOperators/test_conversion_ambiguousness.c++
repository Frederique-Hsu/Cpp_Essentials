/*!
 *  \file       test_conversion_ambiguousness.c++
 *  \brief      
 *  
 */


#include <catch2/catch_test_macros.hpp>
#include <iostream>

class Quad
{
public:
    Quad(double d) : elem{d} 
    {
        std::cout << "Called Quad(double = " << d << ")" << std::endl;
    }

    double element() const
    {
        return elem;
    }
private:
    double elem;
};

Quad operator+(Quad a, Quad b)
{
    return Quad(a.element() + b.element());
}

TEST_CASE("Check the ambiguousness issue of implicit type conversion")
{
    auto fn = [](double a1, double a2) {
        Quad r1 = a1 + a2;
        Quad r2 = Quad{a1} + a2;
        CAPTURE(r1);
        CAPTURE(r2);
        CHECK(true);
    };

    SECTION("which operator+ will be called")
    {
        fn(1.2, 5.6);
    }
}

class Real
{
public:
    Real(double real) : m_real{real} {}
    operator double() 
    { 
        std::cout << "Called operator double()" << std::endl;
        return m_real; 
    }
    operator int() 
    {
        std::cout << "Called operator int()" << std::endl;
        return m_real; 
    }

private:
    double m_real;
};

TEST_CASE("初始化或者赋值操作两侧的数据类型一经确定，他们就会共同被用来进行解析")
{
    auto convert = [](Real a) {
        double d = a;
        CAPTURE(d);

        int i = a;
        CAPTURE(i);

        CHECK(true);
    };

    SECTION("Check which type conversion will be called?")
    {
        convert(Real{3.1415926});
    }
}