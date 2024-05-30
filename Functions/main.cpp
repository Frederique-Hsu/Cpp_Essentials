/*!
 *  \file       main.cpp
 *  \brief      This file implements the main() portal function for current project.
 *
 */


#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    for (int index = 0; index < argc; ++index)
    {
        std::cout << "argv[" << index << "] = " << argv[index] << std::endl;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*================================================================================================*/

struct S
{
    [[noreturn]] virtual inline auto f(const unsigned long int* const) noexcept -> void const;
};
