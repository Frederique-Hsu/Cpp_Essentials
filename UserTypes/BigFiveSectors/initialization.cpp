/*!
 *  \file       initialization.cpp
 *  \brief
 *
 */


#include "initialization.hpp"

#include <limits>
#include <stdexcept>
#include <iostream>
#include <cmath>

Club::Club(const std::string& n, Date fd) : name{n}, founded{fd}
{
}

/*!
 *  \note   引用成员或const成员必须初始化。
 *          对于大多数类型，程序员可以选择使用初始化器还是赋值。通常倾向于使用成员初始化器语法(member initializer syntax)
 *          这能明确表示正在进行初始化操作。
 *          使用初始化器语法与使用赋值相比，通常还有性能上的优势。
 */
Composite::Composite(int number, const std::string& name, Date date, Club& cl)
    : num{number}, club{name, date}, refclub{cl}
{
}

Person::Person(const std::string& name, const std::string& address) : m_name{name}
{
    m_address = address;
}

#if !defined(USE_DELEGATING_CONSTRUCTOR)
void Delegate::validate(int no)
{
    if ((0 < no) && (no < std::numeric_limits<int>::max()))
    {
        number = no;
    }
    else
    {
        throw std::out_of_range("the number is beyond of the scope (0, max)");
    }
}
#endif

Delegate::Delegate(int num)
{
    std::cout << "called the Delegate::Delegate(int) constructor." << std::endl;

    if ((0 < num) && (num < std::numeric_limits<int>::max()))
    {
        number = num;
    }
    else
    {
        throw std::invalid_argument("the number is beyond the scope (0, max)");
    }
}

Delegate::Delegate() : Delegate{42}     // delegating constructor or forwarding constructor
{
    std::cout << "called the delegating constructor Delegate::Delegate()" << std::endl;
}

Delegate::Delegate(const std::string& num_str) : Delegate{std::stoi(num_str)}
{
    std::cout << "called the forwarding constructor Delegate::Delegate(const string&)" << std::endl;
}

int Delegate::getNumber() const
{
    return number;
}

Decryptor::Decryptor()
{
}

int Decryptor::operator()(int cipher)
{
    return cipher;
}

Crypto::Crypto() : m_plaintext{}, m_ciphertext{}
{
}

Crypto::Crypto(int plain) : m_plaintext{plain}, m_ciphertext{}
{
}

Crypto::Crypto(Decryptor decryptor, int cipher) : m_plaintext{}, m_ciphertext{decryptor(cipher)}
{
}


int Node::node_count = 0;   // 在类外部做定义

/*!
 *  \attention  Non-const static data member must be initialized out of class
 */
int Curious::c2 = 11;

const int Curious::c4 = std::sqrt(9);

const float Curious::c5 = 7.0;

const int* ptr = &Curious::c1;
