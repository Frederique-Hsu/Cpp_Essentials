/*!
 *  \file       linear-algebra.cpp
 *  \brief
 *
 */


#include <iostream>
#include <chrono>

#include <eigen3/Eigen/Dense>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " dim" << endl;
        return EXIT_FAILURE;
    }

    cout << "Number of threads used by Eigen: " << Eigen::nbThreads() << endl;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;

    // Allocate matrices and right-hand side vector
    auto start_timestamp = high_resolution_clock::now();
    int dim = atoi(argv[1]);
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(dim, dim);
    Eigen::MatrixXd b = Eigen::VectorXd::Random(dim);
    auto end_timestamp = high_resolution_clock::now();
    cout << "Matrices allocation and initialization expends "
         << duration_cast<chrono::milliseconds>(end_timestamp - start_timestamp).count()
         << " milliseconds." << endl;

    start_timestamp = high_resolution_clock::now();
    // Save matrices and RHS
    Eigen::MatrixXd A1 = A;
    Eigen::MatrixXd b1 = b;
    end_timestamp = high_resolution_clock::now();
    cout << "Scaling done, A and b saved, expends "
         << duration_cast<chrono::milliseconds>(end_timestamp - start_timestamp).count()
         << " milliseconds" << endl;

    start_timestamp = high_resolution_clock::now();
    Eigen::VectorXd x = A.lu().solve(b);
    end_timestamp = high_resolution_clock::now();
    cout << "Linear system solver done, expends "
         << duration_cast<chrono::milliseconds>(end_timestamp - start_timestamp).count()
         << " milliseconds" << endl;

    double relative_error = (A * x - b).norm() / b.norm();
    cout << "relative error = " << relative_error << endl;


    return EXIT_SUCCESS;
}