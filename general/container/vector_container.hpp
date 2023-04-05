/*!
 *  \file       vector_container.hpp
 *  \brief      Study the vector container
 *
 */

#pragma once

#include <string>
#include <vector>
#include <iostream>

struct Entry
{
    std::string name;
    int number;
};

std::ostream& operator<<(std::ostream& os, const Entry& entry);

void print_book(const std::vector<Entry>& book);

/* User-improved Vector container ================================================================*/
template<typename T>
class Vec : public std::vector<T>
{
public:
    using std::vector<T>::vector;   // 使用std::vector的构造函数，但名字是Vec

    T& operator[](int i);       // 范围检查
    const T& operator[](int i) const;       // 常量版本
};

/* Implementation ================================================================================*/
template<typename T>
T& Vec<T>::operator[](int i)
{
    return std::vector<T>::at(i);
}

template<typename T>
const T& Vec<T>::operator[](int i) const
{
    return std::vector<T>::at(i);
}
