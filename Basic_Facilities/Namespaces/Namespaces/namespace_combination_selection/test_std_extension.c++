/*!
 *  \file       test_std_extension.c++
 *  \brief
 *
 */


#include "std_extension.hpp"

#include <boost/test/unit_test.hpp>

template<class T>
void print(const std::vector<T>& vec)
{
    for (auto& elem : vec)
    {
        std::cout << elem << " ";
    }
    std::cout << "\n" << std::endl;
}


BOOST_AUTO_TEST_SUITE(UTest4StdExtension)

BOOST_AUTO_TEST_CASE(CheckExtendedSortAlgorithm)
{
    using namespace std_extension;
    using namespace std;

    vector<int> numbers{8, 13, -5, 28, 103, -35, 68, 0, 256, -99, 103, 28};

    sort(numbers);
    print(numbers);

    sort(numbers, [](int x, int y) { return x >= y; });
    print(numbers);

    sort(numbers.begin(), numbers.end());
    print(numbers);

    sort(numbers.begin(), numbers.end(), [](int x, int y) { return x > y; });
    print(numbers);
}

BOOST_AUTO_TEST_SUITE_END()
