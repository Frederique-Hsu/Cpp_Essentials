/*!
 *  \file       Functor.hpp
 *  \brief
 *
 */


#pragma once



struct Functor
{
    int &imember;

    Functor(int &imem);
    void operator()();
};
