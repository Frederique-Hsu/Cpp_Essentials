/*!
 *  \file       cast.hpp
 *  \brief
 *
 */


#pragma once


#include <stdexcept>

/* Prototype =====================================================================================*/
template<class Target, class Source>
Target narrow_cast(Source src);




/* Implementation ================================================================================*/
template<class Target, class Source>
Target narrow_cast(Source src)
{
    auto target = static_cast<Target>(src);
    if (static_cast<Source>(target) != src)
    {
        throw std::runtime_error("narrow_cast<>() failed.");
    }
    return target;
}
