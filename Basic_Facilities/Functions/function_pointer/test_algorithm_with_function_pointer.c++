/*!
 *  \file       test_algorithm_with_function_pointer.c++
 *  \brief
 *
 */


#include "test_algorithm_with_function_pointer.h++"
#include "function_pointer.hpp"

#include <cstring>
#include <random>


void UTest4FunctionPointerAlgorithm::SetUp()
{
    m_fib_array = new std::uint64_t[N];
    std::memset(m_fib_array, 0, sizeof(int*) * N);
    displayFibonacciArray();

    prepareShuffledFibonacciArray();
}

void UTest4FunctionPointerAlgorithm::TearDown()
{
    delete [] m_fib_array;
}

void UTest4FunctionPointerAlgorithm::prepareShuffledFibonacciArray()
{
    m_fib_array[0] = 1;
    m_fib_array[1] = 1;

    for (auto index = 2UL; index < N; ++index)
    {
        m_fib_array[index] = m_fib_array[index-1] + m_fib_array[index-2];
    }
    std::cout << "Raw Fibonacci array: " << std::endl;
    displayFibonacciArray();

    std::shuffle(m_fib_array, m_fib_array + N - 1, std::mt19937_64(std::random_device()()));
    std::cout << "Shuffled Fibonacci array: " << std::endl;
    displayFibonacciArray();
}

void UTest4FunctionPointerAlgorithm::displayFibonacciArray()
{
    for (auto index = 0UL; index < N; ++index)
    {
        std::cout << *(m_fib_array + index) << "  ";
    }
    std::cout << std::endl;
}

int compare(const void* a, const void* b)
{
    return *(static_cast<const int*>(a)) - *(static_cast<const int*>(b));
}

TEST_F(UTest4FunctionPointerAlgorithm, CheckShellSort)
{
#if (ALGORITHM_ARGUMENT == ALGORITHM_USE_FUNCTION_OBJECT)
    int (*pFn)(const void*, const void*) = &compare;

    shell_sort(m_fib_array, 20, N, pFn);
#elif (ALGORITHM_ARGUMENT == ALGORITHM_USE_FUNCTION_POINTER)
    shell_sort(m_fib_array, 20, N, compare);
#else
    shell_sort(m_fib_array, 20, N,
               [](const void* a, const void* b) -> int
               {
                    return *static_cast<const int*>(a) - *static_cast<const int*>(b);
               });
#endif
    std::cout << "After shell sort, the Fibonacci array becomes: " << std::endl;
    displayFibonacciArray();
}


TEST(UTest4DynamicMemoryArray, HowToDeterminDynamicArrayLength)
{
    constexpr const int LEN = 5;
    int* dynamic_array = new int[LEN];

    auto total_size = sizeof(dynamic_array);
    auto unit_size = sizeof(dynamic_array[0]);
    auto len = total_size / unit_size;
    EXPECT_NE(len, LEN);

    delete [] dynamic_array;

    int static_array[LEN] = {0};
    total_size = sizeof(static_array);
    unit_size = sizeof(static_array[0]);
    len = total_size / unit_size;
    EXPECT_EQ(len, LEN);
}
