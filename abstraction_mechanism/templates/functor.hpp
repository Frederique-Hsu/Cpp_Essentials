/*!
 *  \file   functor.hpp
 *  \brief  Study the function object.
 *  
 */


#pragma once


/* Definition ====================================================================================*/
template<typename T>
class Less_Than
{
private:
    const T val;
public:
    Less_Than(const T& v);
    bool operator()(const T& x) const;
};

template<typename C, typename P> int count(const C& c, P pred);


/* Implementation ================================================================================*/
template<typename T>
Less_Than<T>::Less_Than(const T& v) : val{v}
{
}

template<typename T>
bool Less_Than<T>::operator()(const T& x) const
{
    return x < val;
}

template<typename C, typename P>
int count(const C& c, P pred)
{
    int cnt = 0;
    for (const auto& elem : c)
    {
        if (pred(elem))
        {
            ++cnt;
        }
    }
    return cnt;
}

