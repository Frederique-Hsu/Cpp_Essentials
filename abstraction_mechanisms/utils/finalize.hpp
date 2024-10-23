/*!
 *  \file       finalize.hpp
 *  \brief      
 *  
 */


#pragma once


template<typename FnType> class FinalAction;

template<typename FnType> FinalAction<FnType> finalize(FnType fn);