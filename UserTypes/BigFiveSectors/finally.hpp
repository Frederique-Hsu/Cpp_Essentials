/*!
 *  \file       finally.hpp
 *  \brief
 *
 */


#pragma once

/*!
 *  \section    Prototypes
 */

template<typename FnType> struct FinalAction;


template<class FnType> FinalAction<FnType> finally(FnType fn);

/*================================================================================================*/

#include "finally_impl.hpp"
