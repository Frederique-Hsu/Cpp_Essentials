/*!
 *  \file       lock.hpp
 *  \brief
 *
 */



#pragma once



template<typename M1, typename... Mx> int try_lock(M1& mtx, Mx& tail...)
{
    if (mtx.try_lock())
    {
        int n = try_lock(tail...);
        if (n == -1)
            return -1;
        mtx.unlock();
        return n+1;
    }
    return 1;
}

template<typename M1> int try_lock(M1& mtx)
{
    return (mtx.try_lock() ? -1 : 0);
}
