/*!
 *  \file       type_conversion_operator.cpp
 *  \brief
 *
 */


#include "type_conversion_operator.hpp"

#include <bitset>


void Tiny::assign(int i)
{
    if (i & ~077)
    {
        throw BadRange();
    }
    value = i;
}

Tiny::Tiny(int i)
{
#if !defined(DEBUG)
    std::cout << "called constructor Tiny::Tiny(int i = " << i << ")" << std::endl;
#endif
    assign(i);
}

Tiny& Tiny::operator=(int i)
{
#if !defined (DEBUG)
    std::cout << "called Tiny& Tiny::operator=(int i = " << i << ")" << std::endl;
#endif
    assign(i);
    return *this;
}

Tiny::operator int() const      // convert to int() function
{
#if !defined(DEBUG)
    std::cout << "called Tiny::operator int() const" << std::endl;
#endif
    return value;
}

std::string Tiny::BadRange::what() const
{
    return std::string("The argument had exceeded the range.\n");
}

std::ostream& operator<<(std::ostream& os, const Tiny& obj)
{
    os << "0b" << std::bitset<4>((obj.value & 0xF0) >> 4).to_string();
    os << "'" << std::bitset<4>(obj.value & 0x0F).to_string();
    return os;
}

std::istream& operator>>(std::istream& is, Tiny& obj)
{
    int i = 0;
    is >> i;
    obj = i;
    return is;
}