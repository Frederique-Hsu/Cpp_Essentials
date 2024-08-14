/*!
 *  \file       enumerate.cpp
 *  \brief
 *
 */



#include "enumerate.hpp"

#include <iostream>

void process(Warning key)
{
    switch (key)
    {
    case Warning::green:
        std::cout << "Green light" << std::endl;
        break;
    case Warning::orange:
        break;
    case Warning::red:
        break;
    }
}

constexpr Printer_flags operator|(Printer_flags a, Printer_flags b)
{
    return static_cast<Printer_flags>(static_cast<int>(a) | static_cast<int>(b));
}

constexpr Printer_flags operator&(Printer_flags a, Printer_flags b)
{
    return static_cast<Printer_flags>(static_cast<int>(a) & static_cast<int>(b));
}

void try_to_print(Printer_flags x)
{
    switch (x)
    {
    case Printer_flags::acknowledge:
        break;
    case Printer_flags::busy:
        break;
    case Printer_flags::out_of_black:
        break;
    case Printer_flags::out_of_color:
        break;
    /*! \note   把operator|()和operator&()定义成constexpr函数后，就能把它们用于常量表达式了。 */
    case Printer_flags::out_of_black & Printer_flags::out_of_color:
        break;
    }
}

/*================================================================================================*/

enum class Color_code : char
{
    red,
    yellow,
    green,
    blue
};
