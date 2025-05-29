/*!
 *  \file       traits.hpp
 *  \brief      
 *  
 */


#pragma once


template<typename T> T mean(const T& a, const T& b)
{
    return (a + b)/2.0;
}

/*!
 *  \remark     Traits for type promotion
 */
template<class T> struct MeanTrait
{
    using resultT = T;
};

template<> struct MeanTrait<int>
{
    using resultT = double;
};

template<> struct MeanTrait<double>
{
    using resultT = double;
};

template<class T> 
typename MeanTrait<T>::resultT Mean(const T& a, const T& b)
{
    return (a + b)/2.0;
}