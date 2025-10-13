/*!
 *  \file       meta_class.hpp
 *  \brief      类的元编程
 *  
 */


#pragma once


class FactorialSum
{
private:
    int sum[13] = {0};
    
public:
    constexpr FactorialSum();
    
public:
    constexpr int operator()(int i) const;
    constexpr int operator[](int i) const;
};

void create_constexpr_class();

void print_constexpr_class_object();