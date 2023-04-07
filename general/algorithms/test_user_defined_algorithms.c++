/*!
 *  \file       test_user_defined_algorithms.c++
 *  \brief
 *
 */


#include <CppUTest/CommandLineTestRunner.h>
#include <string>
#include <list>
#include <iostream>

#include "user_defined_algorithms.hpp"

TEST_GROUP(UTester4UserAlgorithms)
{
};

TEST(UTester4UserAlgorithms, CheckFindAllElementsFromContainer)
{
    std::string message("Mary had a little lamb");
    for (auto iter : find_all_elements_from_container(message, 'a'))
    {
        if (*iter != 'a')
            std::cerr << "string bug!" << std::endl;
    }

    std::list<double> numbers{1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    for (auto ptr : find_all_elements_from_container(numbers, 3.3))
    {
        if (*ptr != 3.3)
            std::cerr << "list bug!\n";
    }

    std::vector<std::string> colors{"red", "green", "blue", "orange", "yellow", "black"};
    for (auto iter : find_all_elements_from_container(colors, "blue"))
    {
        if (*iter != "blue")
            std::cerr << "vector bug!\n";
    }

    for (auto iter : find_all_elements_from_container(colors, "green"))
    {
        *iter = "vert";
    }
}
