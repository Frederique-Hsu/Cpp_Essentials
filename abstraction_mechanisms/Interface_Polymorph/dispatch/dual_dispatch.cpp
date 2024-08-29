/*!
 *  \file       dual_dispatch.cpp
 *  \brief      
 *  
 */


#include "dual_dispatch.hpp"

#include <iostream>
#include <typeindex>
#include <typeinfo>

namespace dual_dispatch
{
    Rectangle Circle::box() const
    {
        std::cout << "Circle::box() -> Rectangle" << std::endl;
        return Rectangle();
    }
    
    Rectangle Triangle::box() const
    {
        std::cout << "Triangle::box() -> Rectangle" << std::endl;
        return Rectangle();
    }
    
    #if true
    bool intersect(const Shape& s1, const Shape& s2)
    {
        return intersect(s1.box(), s2.box());
    }
    #else
    bool intersect(const Shape& s1, const Shape& s2)
    {
        auto i = index(type_id(s1), type_id(s2));
        return intersect_tbl[i](s1, s2);
    }
    #endif
    
    bool intersect(const Rectangle& a, const Rectangle& b)
    {
        std::cout << "Rect_a X Rect_b" << std::endl;
        return true;
    }
}