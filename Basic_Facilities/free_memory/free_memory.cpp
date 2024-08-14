/*!
 *  \file       free_memory.cpp
 *  \brief
 *
 */


#include "free_memory.hpp"

#include <iostream>
#include <cstring>
#include <vector>

std::string reverse(const std::string& s)
{
    using namespace std;

    string ss;
    std::cout << std::ios_base::hex << std::endl;

    std::cout << "ss address = " << &ss << std::endl;
    for (int i = s.size()-1; i >= 0; --i)
    {
        ss.push_back(s[i]);
    }
    return ss;      // 直接把ss移动到reverse()之外，而无须拷贝任何元素。
}

char* save_string(const char* p)
{
    char* s = new char[std::strlen(p) + 1];
    std::strcpy(s, p);
    return s;
}

void exhasutMemory()
{
    std::vector<char*> vec;

    try
    {
        while (true)
        {
            char* p = new char[10'000];
            vec.push_back(p);
            p[0] = 'x';
        }
    }
    catch (std::bad_alloc)
    {
        std::cerr << "Memory exhasuted!\n" << std::endl;
    }
}
