/*!
 *  \file       test_object.cpp
 *  \brief      
 *  
 */


#include "Message.hpp"

#include <iostream>

class TestObject
{
public:
    static void run()
    {
        Message say_hello("Hello, CMake World!");
        std::cout << say_hello << std::endl;

        Message say_goodbye("Goodbye, CMake World.");
        std::cout << say_goodbye << std::endl;
    }
};

int main(int argc, char* argv[])
{
    for (auto index = 0; index < argc; ++index)
    {
        std::cout << "argv[" << index << "] = " << std::string(argv[index]) << std::endl;
    }

    TestObject::run();

    return EXIT_SUCCESS;
}