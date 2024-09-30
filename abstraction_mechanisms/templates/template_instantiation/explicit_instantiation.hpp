/*!
 *  \file       explicit_instantiation.hpp
 *  \brief      
 *  
 */


#pragma once


#include <cstddef>

/*!
 *  \section    template declaration
 */

template<typename TargetType, typename SourceType> TargetType convert(SourceType source);





/*!
 *  \section    template definition
 */


#include "explicit_instantiation_impl.hpp"