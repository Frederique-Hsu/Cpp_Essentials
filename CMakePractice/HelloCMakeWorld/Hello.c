/*!
 *  \file       Hello.c
 *  \brief      Study how the CMake manage the project.
 *  
 */


#include <stdio.h>


int main(int argc, char* argv[])
{
    printf("Current C standard number is %ld\n", __STDC_VERSION__);
    printf("Current program is %ld-bits.\n", sizeof(void*) * 8);

    printf("Hello, CMake build world!\n");

    return 0;
}