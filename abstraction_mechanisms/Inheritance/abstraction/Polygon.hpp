/*!
 *  \file       Polygon.hpp
 *  \brief      
 *  
 */


#pragma once


#include "Shape.hpp"

class Polygon : public Shape            // Polygon is still an abstract class
{
public:
    bool is_closed() const override;    // only override the is_closed() method
    // because draw() and rotate() methods had not been overrided in Polygon class
};