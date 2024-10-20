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
 *  \warning    手动控制显式实例化时，不需要声明模板原型了，直接实现即可。
 *              如果多余写了的话，反而对导致重复定义。
 */
// template int convert<int>(double);



/*!
 *  \section    template definition
 */


#include "explicit_instantiation_impl.hpp"