/*!
 *  \file       tuple.hpp
 *  \brief      
 *  
 */


#pragma once

#include <iostream>

#include "../control_structures/select.hpp"


class nil {};

template<typename T1 = nil, typename T2 = nil, typename T3 = nil, typename T4 = nil>
struct Tuple : Tuple<T2, T3, T4>
{
    T1 x;

    using Base = Tuple<T2, T3, T4>;
    Base* base()
    {
        return static_cast<Base*>(this);
    }
    const Base* base() const
    {
        return static_cast<const Base*>(this);
    }

    Tuple(const T1& t1,
          const T2& t2,
          const T3& t3,
          const T4& t4) : Base(t2, t3, t4), x{t1}
    {
    }
};

template<>
struct Tuple<>
{
    Tuple()
    {
    }
};

template<typename T1>
struct Tuple<T1> : Tuple<>
{
    T1 x;

    using Base = Tuple<>;
    Base* base()
    {
        return static_cast<Base*>(this);
    }
    const Base* base() const
    {
        return static_cast<const Base*>(this);
    }

    Tuple(const T1& t1) : Base(), x{t1}
    {
    }
};

template<typename T1, typename T2>
struct Tuple<T1, T2> : Tuple<T2>
{
    T1 x;

    using Base = Tuple<T2>;
    Base* base()
    {
        return static_cast<Base*>(this);
    }
    const Base* base() const
    {
        return static_cast<const Base*>(this);
    }

    Tuple(const T1& t1, const T2& t2) : Base(t2), x{t1}
    {
    }
};

template<typename T1, typename T2, typename T3>
struct Tuple<T1, T2, T3> : Tuple<T2, T3>
{
    T1 x;

    using Base = Tuple<T2, T3>;
    Base* base()
    {
        return static_cast<Base*>(this);
    }
    const Base* base() const
    {
        return static_cast<const Base*>(this);
    }

    Tuple(const T1& t1, const T2& t2, const T3& t3) : Base(t2, t3), x{t1}
    {
    }
};


template<typename T1, typename T2, typename T3, typename T4>
void print_elements(std::ostream& os, const Tuple<T1, T2, T3, T4>& tuple4)
{
    os << tuple4.x << ", ";
    print_elements(os, *tuple4.base());
}

template<typename T1, typename T2, typename T3>
void print_elements(std::ostream& os, const Tuple<T1, T2, T3>& tuple3)
{
    os << tuple3.x << ", ";
    print_elements(os, *tuple3.base());
}

template<typename T1, typename T2>
void print_elements(std::ostream& os, const Tuple<T1, T2>& tuple2)
{
    os << tuple2.x << ", ";
    print_elements(os, *tuple2.base());
}

template<typename T1>
void print_elements(std::ostream& os, const Tuple<T1>& tuple1)
{
    os << tuple1.x;
}

template<>
void print_elements(std::ostream& os, const Tuple<>& tuple0)
{
    os << " ";
}

template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream& os, const Tuple<T1, T2, T3, T4>& tuple)
{
    os << "{ ";
    print_elements(os, tuple);
    os << " }";
    return os;
}


template<typename ReturnType, int N>
struct getNth
{
    template<typename Tuple> static ReturnType& get(Tuple& tuple)
    {
        return getNth<ReturnType, N-1>::template get(*tuple.base());
    }

    template<typename Tuple> static const ReturnType& get(const Tuple& tuple)
    {
        return getNth<ReturnType, N-1>::template get(*tuple.base());
    }
};

template<typename ReturnType>
struct getNth<ReturnType, 0>
{
    template<typename Tuple> static ReturnType& get(Tuple& tuple)
    {
        return tuple.x;
    }

    template<typename Tuple> static const ReturnType& get(const Tuple& tuple)
    {
        return tuple.x;
    }
};


using namespace my;

template<int N, typename T1, typename T2, typename T3, typename T4>
Select<N, T1, T2, T3, T4>& get(Tuple<T1, T2, T3, T4>& tuple)
{
    return getNth<Select<N, T1, T2, T3, T4>, N>::get(tuple);
}

template<int N, typename T1, typename T2, typename T3>
const Select<N, T1, T2, T3>& get(const Tuple<T1, T2, T3>& tuple)
{
    return getNth<Select<N, T1, T2, T3>, N>::get(tuple);
}

template<typename T1, typename T2, typename T3, typename T4>
Tuple<T1, T2, T3, T4> Make_Tuple(const T1& t1,
                                 const T2& t2,
                                 const T3& t3,
                                 const T4& t4)
{
    return Tuple<T1, T2, T3, T4>{t1, t2, t3, t4};
}