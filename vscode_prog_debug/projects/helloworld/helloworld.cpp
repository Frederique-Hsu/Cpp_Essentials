/*!
 *  \file       helloworld.cpp
 *  \brief      Study how to write the C++ program and debug in the VS Code environment on Linux platform.
 *  \author     Frederique Hsu (frederique.hsu@outlook.com)
 *  \date       Sun.    25 Feb. 2024
 *
 */


#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    vector<string> msg{"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}