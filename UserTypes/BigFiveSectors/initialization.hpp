/*!
 *  \file       initialization.hpp
 *  \brief
 *
 */


#pragma once

#include <string>
#include <vector>


enum class Month : unsigned char
{
    Jan = 1,    Feb,    Mar,    Apr,    May,    Jun,
    Jul,        Aug,    Sep,    Oct,    Nov,    Dec,
};

struct Date
{
    int year;
    Month month;
    int day;
};

class Club
{
    std::string name;
    std::vector<std::string> members;
    std::vector<std::string> officiers;
    Date founded;

public:
    Club(const std::string& n, Date fd);
};

class Composite
{
    const int num;
    Club club;
    Club& refclub;

public:
    Composite(int number, const std::string& name, Date date, Club& cl);
};

class Person
{
    std::string m_name;
    std::string m_address;

public:
    Person(const std::string& name, const std::string& address);
    Person(const Person&);
};


#define USE_DELEGATING_CONSTRUCTOR

class Delegate
{
    int number;
public:
    Delegate(int num);
    Delegate();
    Delegate(const std::string& num_str);

private:
#if !defined(USE_DELEGATING_CONSTRUCTOR)
    void validate(int no);
#endif

public:
    int getNumber() const;
};

class Decryptor
{
public:
    Decryptor();

public:
    int operator()(int cipher);
};

class Crypto
{
    using Hash = std::string;
public:
    Crypto();
    Crypto(int plain);
    Crypto(Decryptor decryptor, int cipher);

private:
    int m_plaintext;
    int m_ciphertext;

    /*!
     *  \note   多个不同的构造函数对同一个成员都使用相同的初始化器，为了避免混乱与冗余，
     *          可以为数据成员提炼出唯一的初始化器，而选择在类中初始化该数据成员。
     */
    Hash algorithm{"MD5"};
    std::string state{"Constructor run"};
};

class Node
{
    static int node_count;      // static数据成员在类中仅作为声明
public:
    Node();
};

class Curious
{
public:
    static const int c1 = 7;
private:
    /*!
     *  \note   在少数简单的特殊情况下，在类内声明中初始化static成员也是可能的。
     *          条件就是static成员必须是整数或枚举类型的const，或字面值类型的constexpre，
     *          且初始化器必须是一个常量表达式 constexpr
     *          初始化器不能重复.
     */
    static int c2;
    const int c3 = 13;
    static const int c4;
    static const float c5;

public:
    Curious();
};


template<class T, int N>
class FixedArray
{
public:
    /*!
     *  \note   成员常量的主要用途是为类声明中其他地方用到的常量提供符号名称。
     */
    static constexpr int max = N;

    FixedArray();

private:
    T array[max];
};
