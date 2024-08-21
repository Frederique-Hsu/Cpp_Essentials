/*!
 *  \file       Shape.hpp
 *  \brief      
 *  
 */


#pragma once


class Shape
{
public:
    virtual ~Shape() = default;

public:
    virtual void rotate(int) = 0;
    virtual void draw() const = 0;
    virtual bool is_closed() const = 0;
};