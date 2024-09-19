/*!
 *  \file       function_templates.cpp
 *  \brief      
 *  
 */


#include "function_templates.hpp"

#include <cctype>
#include <cstring>
#include <algorithm>

bool NoCaseComparator::operator()(const std::string& a, const std::string& b)
{
    [[maybe_unused]] auto str_toupper = [](std::string str) -> std::string 
    {
        std::transform(str.begin(), str.end(),
                       str.begin(),
                       [](char c) { return std::toupper(c); });
        return str;
    };
    auto str_tolower = [](std::string str) -> std::string
    {
        std::transform(str.begin(), str.end(),
                       str.begin(),
                       [](char c) { return std::tolower(c); });
        return str;
    };
    
    return std::strcmp(str_tolower(a).c_str(), str_tolower(b).c_str()) < 0;
}