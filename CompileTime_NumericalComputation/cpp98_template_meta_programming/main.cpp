/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#include <iostream>

#include "factorial.hpp"
#include "factorial_template.hpp"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;
    static_assert(__cplusplus == 199711L, "The C++ standard no. you selected is incorrect.");

    // print_factorial();
    // print_static_factorial();
    // print_template_factorial();
    print_template_factorial_enumerator();

    return 0;
}
