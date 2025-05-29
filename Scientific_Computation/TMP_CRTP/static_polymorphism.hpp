/*!
 *  \file       static_polymorphism.hpp
 *  \brief      
 *  
 */


#pragma once


/*!
 *  \remarks    C++ virtual functions have some overhead at run-time, it will ruin the 
 *              performance of any algorithm.
 *              It was called the dynamic-polymorphism feature, it is not recommended.
 * 
 *              We will now study a static polymorphism alternative.
 * 
 *  \brief      CRTP idiom
 * 
 *  \details    The "Curiously Recurring Template Pattern (CRTP)" is a C++ idiom that specializes
 *              a base class using the derived class as a template.
 */

// declare base class with derived class as a template's type argument
template<class Derived> class Base
{
};

// seemingly recursive definition of a derived class
class SomeDerivedClass : public Base<SomeDerivedClass>
{
};


template<class Derived> class Matrix
{
public:
    Derived& FromDerived();

    double operator()(int row_index, int col_index);
};

class SymmetricMatrix : public Matrix<SymmetricMatrix>
{
public:
    double operator()(int row, int col);
};

class UpperTriangularMatrix : public Matrix<UpperTriangularMatrix>
{
public:
    double operator()(int row, int col);
};