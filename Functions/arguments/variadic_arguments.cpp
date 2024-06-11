/*!
 *  \file       variadic_arguments.cpp
 *  \brief
 *
 */


#include "variadic_arguments.hpp"

#include <cstdarg>
#include <iostream>

void error(int severity ...)
{
    va_list ap;
    va_start(ap, severity);

    while (true)
    {
        char* p = va_arg(ap, char*);
        if (p == NULL)
        {
            break;
        }
        std::cerr << p << " ";
    }

    va_end(ap);
    std::cerr << "\n";

    if (severity)
    {
        exit(severity);
    }
}

void error(int severity, std::initializer_list<std::string> err)
{
    for (auto& s : err)
    {
        std::cerr << s << " ";
    }
    std::cerr << std::endl;

    if (severity)
    {
        exit(severity);
    }
}

void error(int severity, const std::vector<std::string>& err)
{
    for (auto& s : err)
    {
        std::cerr << s << " ";
    }
    std::cerr << std::endl;

    if (severity)
    {
        exit(severity);
    }
}

std::vector<std::string> arguments(int argc, char* argv[])
{
    std::vector<std::string> res;
    for (int i = 0; i < argc; ++i)
    {
        res.push_back(argv[i]);
    }
    return res;
}
