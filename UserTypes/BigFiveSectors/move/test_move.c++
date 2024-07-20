/*!
 *  \file       test_move.c++
 *  \brief
 *
 */


#include "move.hpp"
#include "../copy/matrix.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <initializer_list>

SCENARIO("Make the unit testing for move and swap operations")
{
    GIVEN("Define several big objects")
    {
        std::string long_sentence = "The fundamental problem is that we really didn’t want "
                                    "to do any copying at all: we just wanted to exchange pairs of values.";

        std::string paragraph = "We can also look at the issue of copying from a completely different "
                                "point of view: we don’t usually copy physical things unless we absolutely "
                                "have to. If you want to borrow my phone, I pass my phone to you rather "
                                "than making you your own copy. If I lend you my car, I give you a key and "
                                "you drive away in my car, rather than in your freshly made copy of my car. "
                                "Once I have given you an object, you have it and I no longer do.";

        using City = std::string;
        std::vector<City> chinese_cities{"北京", "上海", "杭州", "深圳", "广州",
                                         "武汉", "成都", "西安", "重庆", "哈尔滨"};

        std::vector<City> american_cities{"New York", "Washington D.C.", "Los Angeles", "Chicago", "Houston",
                                          "Phoenix", "Philadelphia", "San Antonia", "San Diego", "Dallas",
                                          "Austin", "Indianapolis", "San Francisco", "Seattle"};

        auto print = [](const std::vector<City>& cities) {
            for (auto& city : cities)
            {
                std::cout << city << ",  ";
            }
            std::cout << "\n" << std::endl;
        };

        // print(chinese_cities);
        // print(american_cities);

        WHEN("Define a high-efficient swapping utility to change between each other")
        {
            using std::string;
            using std::vector;

            auto high_efficient_swap = [](string& s1,                   string& s2,
                                          vector<string>& vs1,          vector<string>& vs2,
                                          Matrix<unsigned>& matrix_a,   Matrix<unsigned>& matrix_b) {
                swap(s1, s2);
                swap(vs1, vs2);
                swap(matrix_a, matrix_b);
            };

            auto generate_fibonacci = [](unsigned length = 2) {
                std::vector<unsigned> fibonacci;

                fibonacci.push_back(1);
                fibonacci.push_back(1);

                for (unsigned index = 2; index < length; ++index)
                {
                    fibonacci.push_back(fibonacci[index-1] + fibonacci[index-2]);
                }
                return fibonacci;
            };

            Matrix<unsigned> mat_a(5, 8);

            mat_a.assign(generate_fibonacci(5 * 8));

            // std::cout << "Matrix A = \n" << mat_a;

            Matrix<unsigned> mat_b(mat_a.row(), mat_a.column());
            unsigned array[mat_b.row() * mat_b.column()];

            for (auto index = 0; index < mat_b.row() * mat_b.column(); ++index)
            {
                array[index] = index;
            }
            mat_b.assign(array, mat_b.size());
            // std::cout << "Matrix B = \n" << mat_b;

            THEN("Make the swapping, and check them")
            {
                auto raw_long_sentence = long_sentence;
                auto raw_paragraph = paragraph;
                auto raw_chinese_cities = chinese_cities;
                auto raw_american_cities = american_cities;
                auto raw_mat_a = mat_a;
                auto raw_mat_b = mat_b;

                high_efficient_swap(long_sentence, paragraph, chinese_cities, american_cities, mat_a, mat_b);
                #if false
                std::cout << "long_sentence = " << long_sentence << std::endl;
                std::cout << "paragraph = " << paragraph << std::endl;
                print(chinese_cities);
                print(american_cities);
                std::cout << "mat_a = " << mat_a << std::endl;
                std::cout << "mat_b = " << mat_b << std::endl;
                #else
                REQUIRE(raw_long_sentence == paragraph);
                REQUIRE(raw_paragraph == long_sentence);
                REQUIRE(raw_chinese_cities == american_cities);
                REQUIRE(raw_american_cities == chinese_cities);
                REQUIRE(raw_mat_a == mat_b);
                REQUIRE(raw_mat_b == mat_a);
                #endif
            }

            THEN("Add 2 matrices")
            {
                auto mat_sum = mat_a + mat_b;

                REQUIRE((mat_sum.row() == mat_a.row() and mat_sum.column() == mat_b.column()));
            }
        }
    }
}
