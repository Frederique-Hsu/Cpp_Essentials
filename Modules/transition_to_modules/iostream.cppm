/*!
 *  \file       iostream.cppm
 *  \brief      Transition from traditional #include <iostream> to modular import iostream
 *  
 *  
 */


module;

#include <iostream>

export module iostream;

export namespace std
{
    using cout;
    using cin;
    using endl;
    using cerr;
    using clog;
}