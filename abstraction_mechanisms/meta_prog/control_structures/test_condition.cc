/*!
 *  \file       test_condition.cc
 *  \brief      
 *  
 */


#include "condition.hpp"
#include "condition.cpp"

#include "../../utils/finalize.hpp"
#include "../../utils/finalize.cpp"


#include <boost/test/unit_test.hpp>

#include <complex>


BOOST_AUTO_TEST_SUITE(UTest4Condition)

    template<typename T>
    class Complex
    {
    public:
        Complex(const T& real, const T& imag) : m_real{real}, m_imag{imag} {}
    private:
        T m_real;
        T m_imag;
    public:
        T& real() { return m_real; }
        T& imag() { return m_imag; }
    };

    void test(SmartPointer<Complex<double>>& q)
    {
        auto obj = *q;
        BOOST_CHECK(typeid(obj) == typeid(Complex<double>));

        auto real_value = q->real();
        BOOST_CHECK(typeid(real_value) == typeid(double));
    }

    BOOST_AUTO_TEST_CASE(CheckSmartPointer)
    {
        // SmartPointer<double> p{new double{3.14}};
        SmartPointer<Complex<double>> q{new Complex<double>(3.0, 4.0)};
        test(q);
    }


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(UTest4Vector)

    BOOST_AUTO_TEST_CASE(CheckVectorBetweenBeginAndEndIter)
    {
        my::Vector<int> vec1(10, 20);
        
        std::vector<int> std_vec(10, 20);
        my::Vector<int> vec2(std_vec.begin(), std_vec.end());
    }

    template<typename T>
    auto fn(const T& x)
    {
        Enable_If<(20 > sizeof(T)), T> tmp_var = x;
        Enable_If<(20 > sizeof(T)), T*> tmp_ptr = new T{x};

        auto deleter = finalize([&]() {
            if (tmp_ptr != nullptr)
            {
                std::cout << "already delete the pointer." << std::endl;
                delete tmp_ptr;
            }
        });
        return tmp_var + *tmp_ptr;
    }

    BOOST_AUTO_TEST_CASE(CheckEnableIf)
    {
        auto result = fn(10);
        BOOST_CHECK_EQUAL(result, 20);
    }

BOOST_AUTO_TEST_SUITE_END()