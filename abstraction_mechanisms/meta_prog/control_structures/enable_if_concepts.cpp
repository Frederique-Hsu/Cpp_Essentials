/*!
 *  \file       enable_if_concept.cpp
 *  \brief      
 *  
 */


#include "enable_if_concepts.hpp"

/*!
 *  \section    Definition
 */

struct substitution_failure
{
};

template<typename T>
struct substitution_succeeded : std::true_type
{
};

template<>
struct substitution_succeeded<substitution_failure> : std::false_type
{
};

template<typename T>
struct has_fn : substitution_succeeded<typename get_fn_result<T>::type>
{
};

template<typename T>
struct get_fn_result
{
private:
    template<typename X> static auto check(X const& x) -> decltype(fn(x));  // 可以调用fn(x)
    static substitution_failure check();                          // 不能调用fn(x)
public:
    using type = decltype(check(std::declval<T>()));
};

/*!
 *  \section    Implementation
 */


template<typename IterType, typename ValType>
Enable_If<Has_Not_Equals<IterType>(), IterType> find(IterType first, IterType last, ValType val)
{
    IterType it = first;
    while ((it != last) && (*it != val))
    {
        ++it;
    }
    return it;
}

template<typename IterType, typename ValType>
Enable_If<!Has_Not_Equals<IterType>(), IterType> find(IterType first, IterType last, ValType val)
{
    IterType it = first;
    while (!(it == last) && !(*it == val))
    {
        ++it;
    }
    return it;
}