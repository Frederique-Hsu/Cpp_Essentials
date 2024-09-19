/*!
 *  \file   test_Template_Vector.cpp
 *  \brief  Make the unit test for the Vector template.
 *  
 */


#include "Vector.hpp"

#include <gtest/gtest.h>
#include <string>
#include <list>
#include <complex>
#include <iostream>

TEST(UTester4VectorTemplate, VerifyVectorInstance)
{
    Template::Vector<char> vc(200);
    Template::Vector<std::string> vs(17);
    Template::Vector<std::list<int>> veclist(45);
}

#if 0
void for_each(Template::Vector<std::string>& vs)
{
    for (auto& s : vs)
    {
        std::cout << s << std::endl;
    }
}
#endif

void user(std::list<double>& ld, std::vector<std::complex<double>>& vc)
{
    // double d = sum(vi, 0.0);
    double dd = sum(ld, 0.0);
    [[maybe_unused]] auto z = sum(vc, std::complex<double>{});
}