/*!
 *  \file       test_dispatch.h++
 *  \brief      
 *  
 */


#pragma once

#include <boost/test/unit_test.hpp>

namespace dynamic_dispatch
{
    class Triangle;
    class Circle;
}

namespace dual_dispatch
{
    class Triangle;
    class Circle;
}

class Expr;
class Stmt;
class Do1_visitor;
class Do2_visitor;

BOOST_AUTO_TEST_SUITE(UTest4_Dispatch)

    void test_dynamic_dispatch(dynamic_dispatch::Triangle& triangle, 
                               dynamic_dispatch::Circle& circle);
    
    void test_dual_dispatch(dual_dispatch::Triangle& triangle, 
                            dual_dispatch::Circle& circle);
                            
    void test_visitor_pattern_dispatch(Expr& e, Stmt& s, Do1_visitor& do1, Do2_visitor& do2);

BOOST_AUTO_TEST_SUITE_END()