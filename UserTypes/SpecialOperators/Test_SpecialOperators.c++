/*!
 *  \file       Test_SpecialOperators.c++
 *  \brief      
 *  
 */


#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include <list>

#include "SpecialOperators.hpp"

TEST_CASE("Apply the Assoc and its operators", "[.][Assoc][Operators]")
{
    Assoc values;

    SECTION("Enter the buffer to feed into Assoc")
    {
        std::string buffer;
        while (std::cin >> buffer)
        {
            ++values[buffer];
        }
        for (auto& value : values.vec)
        {
            // std::cout << "{" << value.first << ", " << value.second << "}" << std::endl;
            UNSCOPED_INFO("{" << value.first << ", " << value.second << "}\n");
        }

        CHECK(true);
    }
}

std::ostringstream& operator<<(std::ostringstream& oss, const std::pair<int, int>& obj)
{
    oss << "pair{" << obj.first << ", " << obj.second << "}\n";
    return oss;
}

TEST_CASE("Check the functor invokation", "[functors]")
{
    auto fn = [](Action act) {
        int x = act(-2);
        CAPTURE(x);

        auto y = act(-5, 10);
        std::ostringstream oss;
        oss << y;
        INFO("y := " << oss.str());

        double z = act(3.2);
        CAPTURE(z);

        CHECK(true);
    };

    SECTION("Invoke the functors")
    {
        Action compute;
        fn(compute);
    }
}

SCENARIO("Make the unit testing for class functors", "[class functor]")
{
    GIVEN("Define a comprehensive function, based on the Add class")
    {
        auto hg = [](std::vector<std::complex<double>>& complex_vec,
                     std::list<std::complex<double>>& complex_list,
                     std::complex<double> z)
        {
            std::for_each(complex_vec.begin(), complex_vec.end(), Add{2, 3});
            // my::for_each(complex_list.begin(), complex_list.end(), Add{z});
            my::for_each(complex_list.begin(), 
                         complex_list.end(), 
                         [z](std::complex<double>& a) { a += z; });
        };

        WHEN("Defined a series of complexes, and the trait complex")
        {
            std::complex<double> a{1, 2}, b{3, 4}, c{5, 6}, d{7, 8}, e{9, 10};
            std::complex<double> minus_a{-1, -2}, minus_b{-3, -4}, minus_c{-5, -6}, minus_d{-7, -8}, minus_e{-9, -10};
            
            using Complex = std::complex<double>;
            std::vector<Complex> complex_vec{a, b, c, d, e};
            std::list<Complex> complex_list{minus_a, minus_b, minus_c, minus_d, minus_e};
            Complex trait{10, -10};

            THEN("Call the hg() function to check whether those complexes had changed.")
            {
                hg(complex_vec, complex_list, trait);
                CAPTURE(a, b, c, d, e);
                CAPTURE(minus_a, minus_b, minus_c, minus_d, minus_e);

                CHECK(true);
            }
        }
    }
}