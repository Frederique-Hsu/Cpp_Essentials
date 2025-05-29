/*!
 *  \file       static_polymorphism.cpp
 *  \brief      
 *  
 */


#include "static_polymorphism.hpp"


template<class Derived>
Derived& Matrix<Derived>::FromDerived()
{
    return static_cast<Derived&>(*this);
}

/*!
 *  \brief  At compile time, send Matrix(row, col) to Derived(row, col)
 */
template<class Derived>
double Matrix<Derived>::operator()(int row_index, int col_index)
{
    return FromDerived()(row_index, col_index);
}