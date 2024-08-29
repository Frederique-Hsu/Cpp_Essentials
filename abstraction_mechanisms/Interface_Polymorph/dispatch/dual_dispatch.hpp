/*!
 *  \file       dual_dispatch.hpp
 *  \brief      
 *  
 */


#pragma once

namespace dual_dispatch
{
    class Rectangle
    {
    };
    
    class Shape
    {
    public:
        virtual ~Shape() = default;
    public:
        virtual Rectangle box() const = 0;
    };
    
    class Circle : public Shape
    {
    public:
        Rectangle box() const override;
    };
    
    class Triangle : public Shape
    {
    public:
        Rectangle box() const override;
    };
    
    bool intersect(const Rectangle& a, const Rectangle& b);
    bool intersect(const Shape& s1, const Shape& s2);
}