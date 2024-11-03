/*!
 *  \file       unit.hpp
 *  \brief      
 *  
 */


#pragma once

#include <string>
#include <iostream>

template<int M, int K, int S>
struct Unit
{
    enum MKS
    {
        m = M,  // length unit: meter
        kg = K, // mass unit: kilogram
        s = S   // time unit: second
    };
};

using Meter = Unit<1, 0, 0>;
using Kilogram = Unit<0, 1, 0>;
using Second = Unit<0, 0, 1>;
using Speed = Unit<1, 0, -1>;
using Acceleration = Unit<1, 0, -2>;

template<typename Unit1, typename Unit2>
struct Uplus
{
    using type = Unit<(Unit1::m + Unit2::m), (Unit1::kg + Unit2::kg), (Unit1::s + Unit2::s)>;
};

template<typename Unit1, typename Unit2>
using Unit_Plus = typename Uplus<Unit1, Unit2>::type;

template<typename Unit1, typename Unit2>
struct Uminus
{
    using type = Unit<static_cast<int>(Unit1::m) - static_cast<int>(Unit2::m),
                      static_cast<int>(Unit1::kg) - static_cast<int>(Unit2::kg),
                      static_cast<int>(Unit1::s) - static_cast<int>(Unit2::s)>;
};

template<typename Unit1, typename Unit2>
using Unit_Minus = typename Uminus<Unit1, Unit2>::type;


template<typename U>
struct Quantity
{
    double val;
    constexpr explicit Quantity(double d) : val{d} {}
};

template<typename U>
Quantity<U> operator+(Quantity<U> x, Quantity<U> y)
{
    return Quantity<U>{x.val + y.val};
}

template<typename U>
Quantity<U> operator-(Quantity<U> x, Quantity<U> y)
{
    return Quantity<U>{x.val - y.val};
}

template<typename U1, typename U2>
Quantity<Unit_Plus<U1, U2>> operator*(Quantity<U1> x, Quantity<U2> y)
{
    return Quantity<Unit_Plus<U1, U2>>{x.val * y.val};
}

template<typename U1, typename U2>
Quantity<Unit_Minus<U1, U2>> operator/(Quantity<U1> x, Quantity<U2> y)
{
    return Quantity<Unit_Minus<U1, U2>>{x.val / y.val};
}

template<typename U>
Quantity<U> operator*(Quantity<U> x, double y)
{
    return Quantity<U>{x.val * y};
}

template<typename U>
Quantity<U> operator*(double x, Quantity<U> y)
{
    return Quantity<U>{x * y.val};
}

template<typename T>
bool operator==(const Quantity<T>& x, const Quantity<T>& y)
{
    return x.val == y.val;
}

template<typename T>
bool operator!=(const Quantity<T>& x, const Quantity<T>& y)
{
    return x.val != y.val;
}

constexpr Quantity<Meter> operator""_m(long double ld)      // m
{
    return Quantity<Meter>{static_cast<double>(ld)};
}

constexpr Quantity<Kilogram> operator""_kg(long double ld)  // kg
{
    return Quantity<Kilogram>{static_cast<double>(ld)};
}

constexpr Quantity<Second> operator""_s(long double ld)     // second
{
    return Quantity<Second>{static_cast<double>(ld)};
}

constexpr Quantity<Meter> operator""_km(long double d)      // km
{
    return Quantity<Meter>{static_cast<double>(1000 * d)};
}

constexpr Quantity<Kilogram> operator""_g(long double d)    // g
{
    return Quantity<Kilogram>{static_cast<double>(d / 1000.0)};
}

constexpr Quantity<Kilogram> operator""_mg(long double d)    // mg
{
    return Quantity<Kilogram>{static_cast<double>(d / 1'000'000)};
}

constexpr Quantity<Second> operator""_ms(long double d)     // ms
{
    return Quantity<Second>{static_cast<double>(d / 1000)};
}

constexpr Quantity<Second> operator""_us(long double d)     // us
{
    return Quantity<Second>{static_cast<double>(d / 1'000'000)};
}

constexpr Quantity<Second> operator""_ns(long double d)     // ns
{
    return Quantity<Second>{static_cast<double>(d / 1'000'000'000)};
}

template<typename U>
Quantity<Unit_Plus<U, U>> square(Quantity<U> x)
{
    return Quantity<Unit_Plus<U, U>>{x.val * x.val};
}

std::string suffix(int u, const char* unit_str)
{
    std::string suf;
    if (u)
    {
        suf += unit_str;
        if (1 < u)
        {
            suf += '0' + u;
        }
        if (u < 0)
        {
            suf += '-';
            suf += '0' - u;
        }
    }
    return suf;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Quantity<U>& v)
{
    return os << v.val << suffix(U::m, "m") << suffix(U::kg, "kg") << suffix(U::s, "s");
}