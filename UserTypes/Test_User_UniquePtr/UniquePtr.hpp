/*!
 *  \file       UniquePtr.hpp
 *  \brief
 *
 */


#pragma once

#include <iostream>

template<typename T> class UniquePtr;

template<typename T> std::ostream& operator<<(std::ostream& os, const UniquePtr<T>& ptr);



#include "UniquePtr_Impl.hpp"