/*!
 *  \file       linear-algebra.cpp
 *  \brief
 *
 */


#include "CxxBLAS.hpp"
#include "CxxLAPACK.hpp"


#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " dim" << std::endl;
        return EXIT_FAILURE;
    }

    /*!
     *  \brief  Generating a uniform distribution of real number
     *          between -1.0 and 1.0
     */
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    // Allocate matrices and right-hand side vector
    int dim = std::atoi(argv[1]);
    std::vector<double> A(dim * dim);
    std::vector<double> b(dim);
    std::vector<int> ipiv(dim);

    // Fill matrix and RHS with random numbers between -1.0 and 1.0
    for (int row = 0; row < dim; ++row)
    {
        for (int col = 0; col < dim; ++col)
        {
            A[row + col * dim] = dist(mt);
        }
        b[row] = dist(mt);
    }

    // Scale RHS vector by a random number between -1.0 and 1.0
    C_DSCAL(dim, dist(mt), b.data(), 1);
    std::cout << "C_DSCAL done" << std::endl;

    // Save matrix and RHS
    std::vector<double> A1(A);
    std::vector<double> b1(b);

    int info = C_DGESV(dim, 1, A.data(), dim, ipiv.data(), b.data(), dim);
    std::cout << "C_DGESV done" << std::endl;
    std::cout << "info is " << info << std::endl;

    double epsilon = 0.0;
    for (int i = 0; i < dim; ++i)
    {
        double sum = 0.0;
        for (int j = 0; j < dim; ++j)
        {
            sum += A1[i + j * dim] + b[j];
        }
        epsilon += std::abs(b1[i] - sum);
    }
    std::cout << "check is " << epsilon << std::endl;

    return EXIT_SUCCESS;
}