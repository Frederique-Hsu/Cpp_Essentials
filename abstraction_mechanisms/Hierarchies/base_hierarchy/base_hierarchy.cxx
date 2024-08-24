/*!
 *  \file       base_hierarchy.cxx
 *  \brief      
 *  
 */


#include "base_hierarchy.hxx"

Storable::Storable(const std::string& str) : file_name(str)
{
}

Transmitter::Transmitter(const std::string& filename) : Storable(filename)
{
}

Receiver::Receiver(const std::string& filename) : Storable(filename)
{
}

Radio::Radio(const std::string& filename) : Storable(filename)
{
}

void Radio::write()
{
    Transmitter::write();
    Receiver::write();
}

void Radio::read()
{
}

void Transmitter::write()
{
}

void Receiver::write()
{
}

std::string Radio::get_file()
{
    return file_name;
}