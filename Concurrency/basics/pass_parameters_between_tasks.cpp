/*!
 *  \file       pass_parameters_between_tasks.cpp
 *  \brief
 *
 */


#include <thread>
#include <vector>
#include <iostream>


void fnct(std::vector<double>& vec);

class Functor
{
    std::vector<double>& m_vec;
public:
    Functor(std::vector<double>& vec);
    void operator()();
};


int main()
{
    std::vector<double> odd_vec{1, 3, 5, 7, 9};
    std::vector<double> even_vec{2, 4, 6, 8, 10};

    std::thread fnct_thread(fnct, std::ref(odd_vec));
    std::thread functor_thread(Functor{even_vec});

    fnct_thread.join();
    functor_thread.join();

    return 0;
}


void fnct(std::vector<double>& vec)
{
    std::cout << "Display the odd numbers: " << std::endl;
    for (auto& number : vec)
    {
        std::cout << number << ", ";
    }
    std::cout << "\n" << std::endl;
}

Functor::Functor(std::vector<double>& vec) : m_vec(vec)
{
}

void Functor::operator()()
{
    std::cout << "Display the even numbers: " << std::endl;
    for (auto& number : m_vec)
    {
        std::cout << number << ", ";
    }
    std::cout << "\n" << std::endl;
}
