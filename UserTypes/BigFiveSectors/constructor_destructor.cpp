/*!
 *  \file       constructor_destructor.cpp
 *  \brief
 *
 */


#include "constructor_destructor.hpp"

#include <iostream>


Tracer::~Tracer()
{
    std::clog << "~" << mess;
}

Tracer::Tracer(const std::string& s) : mess{s}
{
    std::clog << mess;
}

bool operator==(const Work& a, const Work& b)
{
    return (a.author == b.author) and (a.name == b.name) and (a.year == b.year);
}

bool operator!=(const Work& a, const Work& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Work& work)
{
    os << "author: " << work.author << std::endl
       << "name: " << work.name << std::endl
       << "year: " << work.year << std::endl;
    return os;
}

int glob{9};
