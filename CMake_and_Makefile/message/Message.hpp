/*!
 *  \file       Message.hpp
 *  \brief      
 *  
 */


#pragma once

#include <iosfwd>
#include <string>


class Message
{
public:
    explicit Message(const std::string& m);
    friend std::ostream& operator<<(std::ostream& os, Message& obj);

private:
    std::string message_;
    std::ostream& printObject(std::ostream& os);
};