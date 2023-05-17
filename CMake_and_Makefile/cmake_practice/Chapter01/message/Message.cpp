/*!
 *  \file       Message.cpp
 *  \brief      
 *  
 */


#include "Message.hpp"

#include <iostream>

Message::Message(const std::string& m) : message_(m)
{
}

std::ostream& operator<<(std::ostream& os, Message& obj)
{
    return obj.printObject(os);
}

std::ostream& Message::printObject(std::ostream& os)
{
    os << "This is my very nice message: " << std::endl;
    os << message_;
    return os;
}