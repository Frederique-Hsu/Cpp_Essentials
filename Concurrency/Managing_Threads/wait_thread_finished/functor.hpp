/*!
 *  \file       functor.hpp
 *  \brief
 *
 */


#pragma once


class Functor
{
private:
    int& imem;

public:
    Functor(int& i);


public:
    void operator()();
};


void waitThreadFinished();
