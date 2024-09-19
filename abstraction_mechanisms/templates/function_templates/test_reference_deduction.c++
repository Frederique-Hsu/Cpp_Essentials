/*!
 *  \file       test_reference_deduction.c++
 *  \brief      
 *  
 */


#include "reference_deduction.hpp"
#include "reference_deduction.cpp"

#include <gtest/gtest.h>

TEST(UTest4ReferenceDeduction, DeduceTheReferenceTypeArgument)
{
    std::string x{"There and back again"};
    
    Xref<std::string> ref1(7, "Here");  // ref1的构造会使用构造函数 Xref(int, string&&)，因为"Here"是一个临时变量，是一个右值
    Xref<std::string> ref2(9, x);       // ref2的构造会使用构造函数 Xref(int, string&),  因为x是一个左值
    Xref<std::string> ref3(3, new std::string{"There"});    // ref3的构造会使用构造函数 Xref(int, string*)
}

TEST(UTest4ReferenceDeduction, RValueReferenceTypeDeduction)
{
    auto p1 = my::make_unique<Xref<std::string>>(7, "Here");
    
    std::string x = "There";
    auto p2 = my::make_unique<Xref<std::string>>(9, x);
}