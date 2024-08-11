/*!
 *  \file       linear_algebra.cpp
 *  \brief
 *
 */



#include <iostream>
#include <chrono>

#include <eigen3/Eigen/Dense>

EIGEN_DONT_INLINE double simple_function(Eigen::VectorXd& va, Eigen::VectorXd& vb)
{
    double d = va.dot(vb);
    return d;
}

int main(int argc, char* argv[])
{
    using namespace std::chrono;

    int len = 100'0000;
    int num_repetitions = 100;

    Eigen::VectorXd va = Eigen::VectorXd::Random(len);
    Eigen::VectorXd vb = Eigen::VectorXd::Random(len);

    double result = double{};
    auto start_timestamp = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_repetitions; ++i)
    {
        result = simple_function(va, vb);
    }
    auto end_timestamp = std::chrono::high_resolution_clock::now();
    auto elapsed_milliseconds = duration_cast<milliseconds>(end_timestamp - start_timestamp).count();

    std::cout << "result = " << result << std::endl;
    std::cout << "elapsed milliseconds = " << elapsed_milliseconds << std::endl;

    return EXIT_SUCCESS;
}