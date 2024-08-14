/*!
 *  \file       type_predicate.hpp
 *  \brief      研究类型谓词
 *
 */


#pragma once

#include <type_traits>
#include <utility>
#include <string>
#include <vector>
#include <iostream>

template<typename Scalar>
class Complex
{
private:
    Scalar real;
    Scalar imag;
public:
    static_assert(std::is_arithmetic<Scalar>(), "I only support complex of arithmetic types.");
};

template<typename T> constexpr bool Is_Arithmetic()
{
    return std::is_arithmetic<T>::value;
}

namespace My
{
    template<typename Forward_iterator, typename T, typename Compare>
    std::pair<Forward_iterator, Forward_iterator> equal_range(Forward_iterator first,
                                                              Forward_iterator last,
                                                              const T& val,
                                                              Compare cmp);
}

class Record
{
public:
    std::string name;
public:
    Record(const std::string& record_name);
};

std::ostream& operator<<(std::ostream& out_stream, const Record& record);

void search_sub_sequence(const std::vector<Record>& records);
