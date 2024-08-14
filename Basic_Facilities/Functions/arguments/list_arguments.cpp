/*!
 *  \file       list_arguments.cpp
 *  \brief
 *
 */


#include "list_arguments.hpp"

#if (LIST_ARGUMENTS == LIST_ARGUMENTS_NOT_OVERLOADED)
void f2(S)
{
    std::cout << "called f2(struct S)" << std::endl;
}

void f4(int)
{
    std::cout << "called f4(int)" << std::endl;
}
#elif (LIST_ARGUMENTS == LIST_ARGUMENTS_OVERLOADED)
void fn(S)
{
    std::cout << "called fn(struct S)" << std::endl;
}

void fn(int)
{
    std::cout << "called fn(int)" << std::endl;
}
#endif
