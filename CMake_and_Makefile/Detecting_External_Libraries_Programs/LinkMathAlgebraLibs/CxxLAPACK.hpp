/*!
 *  \file       CxxLAPACK.hpp
 *  \brief
 *
 */


#pragma once


#include "fc_mangle.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern int DGESV(int* n,    int* nrhs,  double* a,
                 int* lda,  int* ipiv,  double* b,
                 int*,      int*);

#ifdef __cplusplus
}
#endif

int C_DGESV(int n,      int nrhs,   double* a,
            int lda,    int* ipiv,  double* b,
            int ldb);