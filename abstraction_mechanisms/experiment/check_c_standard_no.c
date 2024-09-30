/*!
 *  \file       check_c_standard_no.c
 *  \brief      
 *  
 */


#include <stdio.h>

#if defined (CHECK_C_STANDARD_NO)
    int main(int argc, char* argv[])
    {
        printf("Current C standatd no. is %ld\n", __STDC_VERSION__);
        
        // int x = 2024;
        // printf("The type of variable x is %s\n", typeof(x));
        
        return 0;
    }
#endif
