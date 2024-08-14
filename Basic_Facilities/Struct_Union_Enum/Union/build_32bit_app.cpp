/*!
 *  \file       build_32bit_app.cpp
 *  \brief      Demonstrate how to build out the 32-bit application on 64-bit machine.
 *  
 */



#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard number is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits\n" << std::endl;

    return 0;
}


/*!
 *  \note   How to build out the 32-bit application on a 64-bit machine?
 *          
 *          1. Check your g++ compiler info.
 *             $ g++ -v
 *             It will show you the Target: x86_64-linux-gnu
 * 
 *          2. Install the gcc-multilib and g++-multilib
 *             $ sudo apt install gcc-multilib
 *             $ sudo apt install g++-multilib
 * 
 *          3. Compiler your program with 32-bit
 *             $ g++ -std=c++2a -m32 build_32bit_app.cpp -o build_32bit_app
 * 
 *          4. Run the program
 *             $./build_32bit_app
 *             It will tell whether your program is 32-bits.
 * 
 *          5. You can also compile your program with 64-bit
 *             $ g++ -std=c++2a -m64 build_32bit_app.cpp -o build_64bit_app
 */