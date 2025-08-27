/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#include <iostream>

#include "meta_functions.hpp"
#include "meta_class.hpp"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;
    static_assert(__cplusplus == 201402L, "The C++ standard no. you select is incorrect.");

    // print_factorial_sum();
    // create_constexpr_class();
    print_constexpr_class_object();

    return 0;
}
