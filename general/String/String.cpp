/*!
 *  \file       String.cpp
 *  \brief
 *
 */


#include "String.hpp"

std::string compose(const std::string& name, const std::string& domain)
{
    return name + '@' + domain;
}

void string_plus_operator(std::string& s1, std::string& s2)
{
    s1 = s1 + "\n";     // 追加换行
    s2 += "\n";         // 追加换行
}

