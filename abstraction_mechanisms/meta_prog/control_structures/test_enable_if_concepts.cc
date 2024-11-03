/*!
 *  \file       test_enable_if_concepts.hpp
 *  \brief      
 *  
 */


#include "enable_if_concepts.hpp"
#include "enable_if_concepts.cpp"

#include <boost/test/unit_test.hpp>

#include <complex>
#include <stdexcept>


BOOST_AUTO_TEST_SUITE(UTest4EnableIfConcepts)

    template<typename T> Enable_If<Ordered<T>(), T> fct(T* a, T* b)
    {
        std::cout << "called T fct(T a = " << a << ", T b = " << b << ")" << std::endl;
        [[maybe_unused]] auto result = *a + *b;
        BOOST_CHECK(typeid(result) == typeid(int));
        return result;
    }

    template<typename T> Enable_If<!Ordered<T>(), T> fct(T a, T b)
    {
        std::cout << "called T fct(T a = " << a << ", T b = " << b << ")" << std::endl;
        [[maybe_unused]] auto result = a + b;
        BOOST_CHECK(typeid(result) == typeid(std::complex<int>));
        return result;
    }

    BOOST_AUTO_TEST_CASE(CheckFct)
    {
        auto fn = [](std::vector<int>& vi, std::vector<std::complex<int>>& vc)
        {
            if ((vi.size() == 0) || (vc.size() == 0))
            {
                throw std::runtime_error("Bad fct's argument");
            }

            auto result1 = fct(&vi.front(), &vi.back());
            BOOST_CHECK(result1 == 6);

            auto result2 = fct(vc.front(), vc.back());
            BOOST_CHECK(result2 == std::complex<int>(6, 8));
        };

        auto vi = std::vector<int>{1, 2, 3, 4, 5};
        auto vc = std::vector<std::complex<int>>{std::complex<int>(1, 2),
                                                 std::complex<int>(3, 4),
                                                 std::complex<int>(5, 6)};
        fn(vi, vc);
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(UTest4_SFINAE_HasFn)

    template<typename T>
    class XMen
    {
    public:
        Enable_If<Has_Fn<T>(), void> call_fn(const T& t)
        {
            fn(t);
        }
    private:
        void fn(const T& t);
    };

    template<typename T>
    auto operator!=(const T& a, const T& b) -> decltype(!(a == b))
    {
        return !(a == b);
    }

BOOST_AUTO_TEST_SUITE_END()