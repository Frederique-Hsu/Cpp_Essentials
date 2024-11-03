/*!
 *  \file       test_variadic_templates.cc
 *  \brief      
 *  
 */


#include "variadic_templates.hpp"
#include "variadic_templates.cpp"

#include <boost/test/unit_test.hpp>

#include <stdexcept>
#include <iostream>
#include <vector>
#include <complex>
#include <tuple>

void printf(const char* s)
{
    if (s == nullptr)
    {
        return;
    }

    while (*s)
    {
        if ((*s == '%') && (*++s != '%'))
        {
            throw std::runtime_error("ivalid format: missing arguments");
        }
        std::cout << *s++;
    }
}

BOOST_AUTO_TEST_SUITE(UTest4VariadicTemplates)

    BOOST_AUTO_TEST_CASE(CheckVariadicClassDefinition)
    {
        class Bx
        {
        public:
            Bx(const int x) : m_x{x} {}
        private:
            [[maybe_unused]] int m_x;
        };

        class By
        {
        public:
            By(const double y) : m_y{y} {}
        private:
            [[maybe_unused]] double m_y;
        };

        class Bz
        {
        public:
            Bz(const char* str) : m_str{str} {}
        private:
            std::string m_str;
        };

        X<> x0;
        X<Bx> x1(1);
        X<Bx, By> x2(2, 3.14);
        X<Bx, By, Bz> x3{5, 0.618, "hello"};

        BOOST_CHECK(sizeof(x0) == 1);
        BOOST_CHECK(sizeof(Bx) == 4);
        BOOST_CHECK(sizeof(By) == 8);
        BOOST_CHECK(sizeof(Bz) == 32);

        BOOST_CHECK(sizeof(x1) == 4);
        BOOST_CHECK(sizeof(x2) == 8 + 8);
        BOOST_CHECK(sizeof(x3) == 8 + 8 + 32);
    }

    void g0()
    {
        std::cout << "g0()" << std::endl;
    }
    template<typename T> void g1(const T& t)
    {
        std::cout << "g1(const T& t = " << t << ")" << std::endl;
    }
    void g1d(double d)
    {
        std::cout << "g1d(double d = " << d << ")" << std::endl;
    }
    template<typename T, typename U> void g2(const T& t, const U& u)
    {
        std::cout << "g2(const T& t = " << t << ", const U& u = " << u << ")" << std::endl;
    }
    BOOST_AUTO_TEST_CASE(CheckForward)
    {
        call(g0);
        // call(g1);   // Error: could not deduce template parameter 'F'
        call(g1<int>, 1);
        call(g1<const char*>, "hello");
        call(g1<double>, 1.2345);
        call(g1d, 1.2);
        // call(g1d, "No way!");   // Error: 提供给g1d()的实参类型错误
        // call(g1d, 1.2, "I can't count");    // Error: 提供给g1d()的实参太多
        call(g2<double, std::string>, 1, "world");

        int i = 99;     // i 是左值
        const char* p = "Trying";
        call(g2<double, std::string>, i, p);

        call([]() { std::cout << "lambda()" << std::endl; });
        call([](int i) { std::cout << "lambda(int i = " << i << ")" << std::endl; }, 17);
        call([](int i, double d, const std::string& str) { 
            std::cout << "lambda(int i = " << i 
                      << ", d = " << d
                      << ", str = " << str << ")"
                      << std::endl; },
            128, 3.1415926, "forward");
        call([i]() { std::cout << "lambda(int i = " << i << ")" << std::endl; });
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(UTest4MyTuple)

    template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
    {
        auto index = 0U;
        os << "{";
        for (index = 0U; index < vec.size()-1; ++index)
        {
            os << vec[index] << ", ";
        }
        os << vec[index] << "}";
        return os;
    }

    template<typename T> std::ostream& operator<<(std::ostream& os, const std::complex<T>& cplx)
    {
        os << "{" << cplx.real() << ", " << cplx.imag() << "i}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const std::tuple<>&)
    {
        return os << "{}";
    }

    BOOST_AUTO_TEST_CASE(CheckStdTuple)
    {
        std::tuple<std::string, std::vector<int>, double, std::complex<int>> tpl("my::tuple", 
                                                                                {1, 2, 3, 4, 5}, 
                                                                                98.076528, 
                                                                                std::complex<int>{3, 4});
        auto element1 = std::get<0>(tpl);
        auto element2 = std::get<1>(tpl);
        auto element3 = std::get<2>(tpl);
        auto element4 = std::get<3>(tpl);
        BOOST_CHECK(typeid(element1) == typeid(std::string) && 
                    typeid(element2) == typeid(std::vector<int>) &&
                    typeid(element3) == typeid(double) &&
                    typeid(element4) == typeid(std::complex<int>));

        BOOST_CHECK(sizeof(tpl) == sizeof(element1) + sizeof(element2) + sizeof(element3) + sizeof(element4));

        // std::cout << tpl << std::endl;   // STL does not provide the output stream for tuple<T...> object, it is very hard
    }

BOOST_AUTO_TEST_SUITE_END()