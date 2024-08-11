/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <cstdlib>
#include <string>
#include <iostream>


std::string say_hello();

int main(int argc, char* argv[])
{
    std::cout << say_hello() << std::endl;
    return EXIT_SUCCESS;
}

std::string say_hello()
{
#ifdef IS_WINDOWS
    return std::string("Hello from Windows");
#elif IS_LINUX
    return std::string("Hello from Linux");
#elif IS_MACOS
    return std::string("Hello from macOS");
#else
    return std::string("Hello from an unknown system!");
#endif
}