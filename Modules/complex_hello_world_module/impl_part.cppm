/*!
 *  \file       impl_part.cppm
 *  \brief      
 *  
 */


module;

#include <iostream>
#include <string>

module M:impl_part;

import :interface_part;

std::string W = "world.";

void World()
{
    std::cout << W << std::endl;
}