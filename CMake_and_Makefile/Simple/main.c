/*!
 *  \file       main.c
 *  \brief      This file implements the main() portal function for current project.
 *  
 */



#include <stdio.h>

#include "defs.h"

int main(int argc, char* argv[])
{
    printf("Current C standard no. = %ld\n", __STDC_VERSION__);
    printf("Current program is %ld-bits\n", sizeof(void*) * 8);

    return 0;
}