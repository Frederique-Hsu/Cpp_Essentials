/*!
 *  \file       check_cpp_standard_no.cpp
 *  \brief      
 *  
 */


#include <iostream>


#if defined (CHECK_CPP_STANDARD_NO)
    int main(int argc, char* argv[])
    {
        std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
        
        return 0;
    }
#endif