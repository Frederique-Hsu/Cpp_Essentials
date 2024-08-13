/*!
 *  \file   test_Container.cpp
 *  \brief  Perform the unit test for interface class Container.
 *  
 */

#include "Container.hpp"
#include "Vector_container.hpp"
#include "List_container.hpp"

#include <gtest/gtest.h>

TEST(ContainerUTester, VerifyUserInterfaceClassContainer)
{
    Vector_container vc{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::cout << "Vector container:" << std::endl;
    visit(vc);

    std::cout << "\n" << std::endl;

    List_container lc{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "List container:" << std::endl;
    visit(lc);
}

TEST(ContainerUTest, CheckVirtualFunctionTable)
{
    std::cout << "sizeof(void*) = " << sizeof(void*) << std::endl;
    std::cout << "sizeof(Container) = " << sizeof(Container) << std::endl;
    std::cout << "sizeof(ConcreteContainer) = " << sizeof(ConcreteContainer) << std::endl;

    std::cout << "sizeof(std::list<double>) = " << sizeof(std::list<double>) << std::endl;
    std::cout << "sizeof(List_container) = " << sizeof(List_container) << std::endl;
}