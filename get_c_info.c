/*!
 *  \file   get_c_info.c
 *  \brief  get some version information about C newest standard.
 *  \author Frederique Hsu
 *  \date   Tue.    22 Nov. 2022
 *
 */


#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("Current C standard version no. = %ld\n", __STDC_VERSION__);
    printf("Current C program is %ld-bits.\n", sizeof(void*) * 8);
    return 0;
}

