/*!
 *  \file       generic_algorithms.hpp
 *  \brief      
 *  
 */


#pragma once

template<typename Iter, typename ValueType> ValueType sum(Iter first, Iter last);

template<typename Iter, typename ValueType> ValueType accumulate(Iter first, 
                                                                 Iter last, 
                                                                 ValueType sum = ValueType{});

template<typename Iter, typename ValueType, typename Oper>
ValueType accumulate(Iter first, Iter last, ValueType init, Oper op);