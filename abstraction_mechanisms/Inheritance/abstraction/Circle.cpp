/*!
 *  \file       Circle.cpp
 *  \brief      
 *  
 */


#include "Circle.hpp"

#ifdef DEBUG_WITH_LOG
    #include <iostream>
#endif


Circle::Circle(Point point, int r) : center{point}, radius{r}
{
}

void Circle::rotate(int)
{
#ifdef DEBUG_WITH_LOG
    std::clog << "Called Circle::rotate(int)" << std::endl;
#endif
}

void Circle::draw() const
{
#ifdef DEBUG_WITH_LOG
    std::clog << "Called Circle::draw()" << std::endl;
#endif
}

bool Circle::is_closed() const
{
    return true;
}