/*!
 *  \file       Structs.cpp
 *  \brief      
 *  
 */


#include "Structs.hpp"

#include <iostream>

void print_addr(Address* paddr)
{
    std::cout << paddr->name << "\n"
              << paddr->number << " " << paddr->street << "\n"
              << paddr->town << "\n"
              << paddr->state[0] << paddr->state[1] << " " << paddr->zip
              << std::endl;
}