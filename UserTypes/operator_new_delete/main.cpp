/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include "test_operator_new_delete.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    UTest_CheckOrdinaryOperatorNewDelete();
    std::cout << "\n" << std::endl;

    UTest_CheckOrdinaryOperatorNewDelete_Array();
    std::cout << "\n" << std::endl;

    UTest_CheckOperatorNewDelete_NoThrow();
    std::cout << "\n" << std::endl;

    UTest_CheckOperatorNewDelete_NoThrow_Array();
    std::cout << "\n" << std::endl;

    UTest_CheckOperatorNewDelete_Alignment();
    std::cout << "\n" << std::endl;

    UTest_CheckOperatorNewDelete_Alignment_NoThrow_Array();
    std::cout << "\n" << std::endl;

    UTest_CheckOperatorNewDelete_WithWrongAlignment();
    std::cout << "\n" << std::endl;

    UTest_CheckPlacementNewDelete();
    std::cout << "\n" << std::endl;

    UTest_CheckHowToDeleteMemoryAllocatedByPlacementNew();
    std::cout << "\n" << std::endl;

    UTest_WhenWillPlacementNewDeleteShowSegmentFault();
    std::cout << "\n" << std::endl;

    UTest_CheckClassSpecificOperatorNewDelete();
    std::cout << "\n" << std::endl;

    UTest_CheckClassSpecificOperatorNewDelete_WithConstructorDestructor();
    std::cout << "\n" << std::endl;

    UTest_CheckClassSpecificOperatorNewDelete_Array();
    std::cout << "\n" << std::endl;

    UTest_CheckClassSpecificPlacementNewDelete();
    std::cout << "\n" << std::endl;

    UTest_CheckClassSpecificOperatorNewDelete_WithAlignment();
    std::cout << "\n" << std::endl;

    return 0;
}