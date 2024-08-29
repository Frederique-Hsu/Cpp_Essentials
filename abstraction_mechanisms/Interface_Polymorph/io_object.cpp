/*!
 *  \file       io_object.cpp
 *  \brief      
 *  
 */


#include "io_object.hpp"
#include "io.hpp"

#include <map>
#include <cstdio>

static std::map<std::string, PtrFn> io_map{
    std::pair<std::string, PtrFn>{"IO_Circle", &IO_Circle::new_io},
    std::pair<std::string, PtrFn>{"IO_Triangle", &IO_Triangle::new_io},
};

std::string get_word(std::istream& is)
{
    std::string keyboard_input_str;
    is >> keyboard_input_str;
    return keyboard_input_str;
}

IOObject* get_obj(std::istream& is, std::string& str)
{
    str = get_word(is);
    if (auto fn = io_map[str])
    {
        return fn(is);
    }
    else
    {
        throw UnknownObject();
    }
}

void Shape::draw()
{
    std::printf("Shape* pointer %p is drawing now.\n", static_cast<void*>(this));
}

void Circle::draw()
{
    std::printf("Circle* pointer %p is drawing a circle...\n", static_cast<void*>(this));
}

void Triangle::draw()
{
    std::printf("Triangle* pointer %p is drawing a triangle...\n", static_cast<void*>(this));
}

IOCircle::IOCircle(std::istream& is) : Circle(is)
{
}

IOCircle* IOCircle::clone() const
{
    return new IOCircle(*this);
}

IOObject* IOCircle::new_circle(std::istream& is)
{
    return new IOCircle(is);
}

IOTriangle::IOTriangle(std::istream& is) : Triangle(is)
{
}

IOTriangle* IOTriangle::clone() const
{
    return new IOTriangle(*this);
}

IOObject* IOTriangle::new_triangle(std::istream& is)
{
    return new IOTriangle(is);
}