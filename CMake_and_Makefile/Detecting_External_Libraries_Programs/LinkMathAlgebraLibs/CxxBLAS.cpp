/*!
 *  \file       CxxBLAS.cpp
 *  \brief
 *
 */


#include "CxxBLAS.hpp"

#include <climits>

void C_DSCAL(size_t length, double alpha, double* vec, int inc)
{
    int big_blocks = (int)(length / INT_MAX);
    int small_size = (int)(length % INT_MAX);

    for (int block = 0; block <= big_blocks; ++block)
    {
        double* vec_s = &vec[block * inc * INT_MAX];
        signed int length_s = (block == big_blocks) ? small_size : INT_MAX;
        ::DSCAL(&length_s, &alpha, vec_s, &inc);
    }
}