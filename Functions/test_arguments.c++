/*!
 *  \file       test_arguments.c++
 *  \brief
 *
 */


#include "test_arguments.h++"

#include "arguments.hpp"


TEST(UTest4Arguments, Check_PointerPassedAsValue)
{
    auto fn = [](int* p, int* q) -> void {
        int* pp = find(p, q, 13);

        std::cout << "current p address = " << std::ios_base::hex << p << std::endl;
        std::cout << "current q address = " << q << std::endl;
        std::cout << "pp address = " << pp << std::endl;
    };

    int* numbers{nullptr};

    auto prepareData = [&numbers](std::size_t n) -> bool {
        numbers = static_cast<decltype(numbers)>(alloca(sizeof(decltype(*numbers)) * n));
        if (numbers == nullptr)
        {
            return false;
        }

        for (std::size_t index = 0; index < n; ++index)
        {
            *(numbers + index) = 5 * index + 3;
        }
        return true;
    };

    constexpr const int n = 30;
    EXPECT_EQ(prepareData(n), true);
    for (auto i = 0; i < n; ++i)
    {
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }

    std::cout << std::ios_base::hex << std::endl;
    std::cout << "numbers[0] address = " << numbers << std::endl;
    std::cout << "numbers[" << n - 1 << "] address = " << numbers + n - 1 << std::endl;

    fn(numbers, numbers + n - 1);
}
