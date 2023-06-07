/*!
 *  \file       struct_bit_field.hpp
 *  \brief      
 *  
 */


#pragma once

#include <type_traits>
#include <cstring>

struct PPN                      // R6000物理页编号
{
    unsigned int PFN : 22;      // 页框编号
    int : 3;                    // 未使用
    unsigned int CCA : 3;       // 缓存一致性算法
    bool nonreachable : 1;
    bool dirty : 1;
    bool valid : 1;
    bool global : 1;
};


/*!
 *  \note       Bit-Field
 *              Declares a class data member with explicit size, in bits.
 *              Adjacent bit-field members may (or may not) be packed to share and straddle the individual bytes.
 * 
 *  \remark     A bit-field declaration id a class data member declaration which uses the following declarator:
 *              identifier attr : size;
 * 
 *  \remark     Explanation
 *              1. The type of a bit-field can only be integral or (possibly cv-qualified) enumeration type, 
 *              an unnamed bit-field cannot be declared with a cv-qualified type.
 *              
 *              2. A bit-field cannot be a static data member.
 * 
 *              3. There are no bit-field prvalues: lvalue-to-rvalue conversion always produces an object of the 
 *              underlying type of the bit-field.
 * 
 *              4. The number of bits in a bit-field sets the limit to the range of values it can hold.
 * 
 */

struct S
{
    unsigned int b : 3;     // three-bit unsigned field, allowed values are 0...7
};


/*!
 *  \note   Multiple adjacent bit-fields are usually packed together, 
 *          although this behaviour is implementation-specific.
 */
struct AddressBit
{
    unsigned char b1 : 3;   // first 3 bits (in the first byte) are b1
    unsigned char    : 2;   // next 2 bits  (in the first byte) are blocked out as unused.
    unsigned char b2 : 6;   // 6 bits for b2 - doesn't fit into the first byte ==> start from the 2nd byte
    unsigned char b3 : 2;   // 2 bits for b3 - next and final bits in the 2nd byte.
};

/*!
 *  \note   大小为0的特殊未命名位域可以强制分解填充。它指定下一个位域从其分配单元的开头开始
 */
struct SpecificBitField
{
    unsigned char b1 : 3;
    unsigned char    : 0;   // start a new byte.
    unsigned char b2 : 2;
};

template<class T>
inline constexpr bool is_trivially_copyable_v = std::is_trivially_copyable<T>::value;

template<class To, class From>
std::enable_if_t<sizeof(To) == sizeof(From) &&
                 is_trivially_copyable_v<From> &&
                 is_trivially_copyable_v<To>, 
                 To>
bit_cast(const From& src) noexcept
{
    static_assert(std::is_trivially_constructible_v<To>, 
                  "This implementation additionally requires destination type to be trivially constructible.");

    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
}
