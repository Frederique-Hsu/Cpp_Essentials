/*!
 *  \file       test_dispatch.c++
 *  \brief      
 *  
 */


#include "test_dispatch.h++"

#include "dynamic_dispatch.hpp"
#include "dual_dispatch.hpp"
#include "../visitor_pattern/visitor.hpp"
    
void UTest4_Dispatch::test_dynamic_dispatch(dynamic_dispatch::Triangle& triangle, 
                                            dynamic_dispatch::Circle& circle)
{
    using namespace std;
    using namespace dynamic_dispatch;
        
    vector<pair<Shape*, Shape*>> vec_shapes{pair<Shape*, Shape*>{&triangle, &triangle},
                                            pair<Shape*, Shape*>{&triangle, &circle},
                                            pair<Shape*, Shape*>{&circle, &triangle},
                                            pair<Shape*, Shape*>{&circle, &circle}};
    for (auto pair_shape : vec_shapes)
    {
        pair_shape.first->intersect(*pair_shape.second);
    }
}

void UTest4_Dispatch::test_dual_dispatch(dual_dispatch::Triangle& triangle,
                                         dual_dispatch::Circle& circle)
{
    using namespace std;
    using namespace dual_dispatch;
    
    vector<pair<Shape*, Shape*>> vec_shapes{pair<Shape*, Shape*>{&triangle, &triangle},
                                        pair<Shape*, Shape*>{&triangle, &circle},
                                        pair<Shape*, Shape*>{&circle, &triangle},
                                        pair<Shape*, Shape*>{&circle, &circle}};
    for (auto pair_shape : vec_shapes)
    {
        intersect(*pair_shape.first, *pair_shape.second);
    }
}

void UTest4_Dispatch::test_visitor_pattern_dispatch(Expr& e, Stmt& s, Do1_visitor& do1, Do2_visitor& do2)
{
    using namespace std;
    
    vector<pair<Node*, Visitor*>> nodes_visitors{pair<Node*, Visitor*>{&e, &do1},
                                                 pair<Node*, Visitor*>(&s, &do1),
                                                 pair<Node*, Visitor*>{&e, &do2},
                                                 pair<Node*, Visitor*>{&s, &do2}};
    for (auto& node_visitor : nodes_visitors)
    {
        node_visitor.first->accept(*node_visitor.second);
    }
}

namespace UTest4_Dispatch
{
    BOOST_AUTO_TEST_CASE(CheckHowDynamicDispatchWorks)
    {
        using namespace dynamic_dispatch;
        Triangle my_triangle;
        Circle your_circle;
        
        test_dynamic_dispatch(my_triangle, your_circle);
    }
    
    BOOST_AUTO_TEST_CASE(CheckHowDualDispatchWorks)
    {
        using namespace dual_dispatch;
        Triangle my_triangle;
        Circle your_circle;
        
        test_dual_dispatch(my_triangle, your_circle);
    }
    
    BOOST_AUTO_TEST_CASE(CheckHowVisitorPatternDispatchWorks)
    {
        Expr expr_node;
        Stmt stmt_node;
        
        Do1_visitor do1_visitor;
        Do2_visitor Do2_visitor;
        
        test_visitor_pattern_dispatch(expr_node, stmt_node, do1_visitor, Do2_visitor);
    }
}