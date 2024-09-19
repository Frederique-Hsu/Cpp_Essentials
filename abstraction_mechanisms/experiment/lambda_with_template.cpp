/*!
 *  \file       lambda_with_template.cpp
 *  \brief      
 *  
 */


#include <iostream>

/*!
 *  \warning    Lambda templates are only available from C++14 beginning
 */
auto add = []<typename T>(T t1, T t2)
{
    return t1 + t2;
};


#if defined (ONLY_RESERVED_FOR_LABDA_WITH_TEMPLATE_PROJECT)
    int main(int argc, char* argv[])
    {
        std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
        
        auto result = add(2, 6);
        std::cout << "The result is " << result << std::endl;
        
        return 0;
    }
#endif