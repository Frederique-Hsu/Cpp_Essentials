/*!
 *  \file       type_conversion_operator.hpp
 *  \brief
 *
 */


#pragma once

#include <iostream>
#include <memory>

class Tiny
{
    friend std::ostream& operator<<(std::ostream& os, const Tiny& obj);
    friend std::istream& operator>>(std::istream& is, Tiny& obj);
public:
    /*!
     *  \attention  Do NOT add the 'explicit', because we want the type implicit conversion here.
     */
    /* explicit */ Tiny(int i = 0);

    Tiny& operator=(int i);
    operator int() const;

private:
    char value;

public:
    class BadRange
    {
    public:
        std::string what() const;
    };

private:
    void assign(int i);
};