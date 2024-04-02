/*!
 *  \file       Message.cpp
 *  \brief      
 *  
 */


#include "Message.hpp"

#include <iostream>

Message::Message(const std::string& mesg) : m_message(mesg)
{
}

std::ostream& Message::printObject(std::ostream& os)
{
    os << "This is my very nice message: " << std::endl;
    os << m_message;

    return os;
}

std::ostream& operator<<(std::ostream& os, Message& obj)
{
    return obj.printObject(os);
}