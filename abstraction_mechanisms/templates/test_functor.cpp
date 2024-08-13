/*!
 *  \file   test_functor.cpp
 *  \brief  Make the unit test for function objects.
 *  
 */


#include "functor.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>

#define FUNCTOR         1
#define LAMBDA          2
#define POLICY_OBJECT   LAMBDA

TEST(UTester4Functor, CheckHowToCallFunctor)
{
    Less_Than<int> lti{42};
    Less_Than<std::string> lts{"Starbucks"};

    // EXPECT_TRUE(lti(43));
}

void fnct(const std::vector<int>& vec, const std::list<std::string>& lst, int x, const std::string& s)
{
    std::cout << "number of values less than " << x
    #if (POLICY_OBJECT == FUNCTOR)
              << ":" << count(vec, Less_Than<int>(x)) << std::endl;
    #elif (POLICY_OBJECT == LAMBDA)
              << ":" << count(vec, [&](int a){ return a < x; }) << std::endl;
    #endif
    
    std::cout << "number of values less than " << s
    #if (POLICY_OBJECT == FUNCTOR)
              << ":" << count(lst, Less_Than<std::string>(s)) << std::endl;
    #elif (POLICY_OBJECT == LAMBDA)
              << ":" << count(lst, [&](const std::string& a){ return a < s; }) << std::endl;
    #endif
}

TEST(UTester4Functor, CheckFunctorAsPredicate)
{
    std::vector<int> primes{2, 3, 5, 7, 11, 13};
    std::list<std::string> cities{"Beijing", "Shanghai", "Chengdu", "Guangzhou", "Shenzhen", "Xiamen"};
    fnct(primes, cities, 10, "Wuhan");
}