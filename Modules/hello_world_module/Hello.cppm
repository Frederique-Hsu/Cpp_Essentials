/*!
 *  \file       Hello.cppm
 *  \brief      
 *  
 */


module;

#include <iostream>

export module Hello;    // primary module interface unit

export void hello()
{
    std::cout << "Hello, C++20 module world." << std::endl;
}