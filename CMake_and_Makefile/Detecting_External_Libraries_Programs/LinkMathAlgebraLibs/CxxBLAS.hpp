/*!
 *  \file       CxxBLAS.hpp
 *  \brief
 *
 */


#pragma once

#include "fc_mangle.h"

#include <cstddef>

#ifdef __cplusplus
extern "C"
{
#endif

    extern void DSCAL(int* n, double* alpha, double* vec, int* inc);

#ifdef __cplusplus
}
#endif

void C_DSCAL(size_t length, double alpha, double* vec, int inc);