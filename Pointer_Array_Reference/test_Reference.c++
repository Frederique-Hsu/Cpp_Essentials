/*!
 *  \file       test_Reference.c++
 *  \brief
 *
 */



#include "test_Reference.h++"
#include "Reference.hpp"

#include <random>
#include <chrono>

UTester4Swap::UTester4Swap() : odds(200), evens(400)
{
}

UTester4Swap::~UTester4Swap()
{
}


void UTester4Swap::SetUp()
{
    for (auto index = 0U; index != odds.size(); ++index)
    {
        auto random_num = std::rand() % 20;
        std::size_t odd = ((random_num % 2 == 0) ? (random_num + 1) : random_num);
        odds[index] = odd;
    }

    for (auto& even : evens)
    {
        even = 2 * (std::rand() % 20);
    }
}

void UTester4Swap::TearDown()
{
}


    TEST_F(UTester4Swap, Check3DifferentSwaps)
    {
        using namespace std;

        cout << "Before swap: \nodds = ";
        for (auto& odd : odds)
        {
            cout << odd << ", ";
        }
        cout << "\n" << endl;

        cout << "evens = ";
        for (auto& even : evens)
        {
            cout << even << ", ";
        }
        cout << "\n" << endl;

        auto start_timestamp = chrono::high_resolution_clock::now();
        swap(odds, evens);
        auto stop_timestamp = chrono::high_resolution_clock::now();

        cout << "After swap: \nodds = ";
        for (auto& odd : odds)
        {
            cout << odd << ", ";
        }
        cout << "\n" << endl;

        cout << "evens = ";
        for (auto& even : evens)
        {
            cout << even << ", ";
        }
        cout << "\n" << endl;

        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop_timestamp - start_timestamp).count();
        #if (SWAP == OLD_STYLE_SWAP)
        cout << "The old style swap had costed " << duration << " ns." << endl;
        #elif (SWAP == RVALUE_REF_STYLE_SWAP)
        cout << "The rvalue-ref style swap had costed " << duration << " ns." << endl;
        #elif (SWAP == MOVE_STYLE_SWAP)
        cout << "The move style swap had costed " << duration << " ns." << endl;
        #endif
    }


    TEST(UTester4DifferentTypeSwap, CheckWhether2DifferentTypeCanSwap)
    {
        GTEST_SKIP();
        std::string my_name{"Frederique Hsu"};
        std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        different_type_swap(my_name, numbers);

        std::cout << my_name << std::endl;
    }
