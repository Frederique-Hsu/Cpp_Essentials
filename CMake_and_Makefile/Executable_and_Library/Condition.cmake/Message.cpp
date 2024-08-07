/*!
 *  \file       Message.cpp
 *  \brief
 *
 */


#include "Message.hpp"

#include <iostream>

Message::Message(const std::string& msg) : m_message{msg}
{
}

std::ostream& Message::printObject(std::ostream& os) const
{
    os << "This is my very nice message: " << std::endl;
    os << m_message;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Message& obj)
{
    return obj.printObject(os);
}