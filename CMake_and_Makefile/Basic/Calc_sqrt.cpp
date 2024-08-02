/*!
 *  \file       Calc_sqrt.cpp
 *  \brief      Calculate the square root of a number.
 *  
 */


#include <iostream>
#include <cmath>
// #include <cstdlib.h>
#include "Config.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        /* Reporting the version number */
        std::cout << argv[0] << " Version " << Sqrt_VERSION_MAJOR << "." 
                  << Sqrt_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    // const double input_value = atof(argv[1]);
    const double input_value = std::stod(argv[1]);      // require C++11 standard feature

    double output_value = sqrt(input_value);
    std::cout << "The square root of " << input_value << " is " << output_value << std::endl;
    return 0;
}