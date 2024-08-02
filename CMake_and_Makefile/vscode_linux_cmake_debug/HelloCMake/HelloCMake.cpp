/*!
 *  \file       helloCMake.cpp
 *  \brief      Study how to use the VS Code to debug C++ program with CMake.
 *
 */

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  cout << "Hello, VS Code and CMake!" << std::endl;

  for (auto index = 0; index < argc; ++index) {
    cout << "argv[" << index << "] = " << string(argv[index]) << std::endl;
  }

  std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
  std::cout << "Current program is " << sizeof(void *) * 8 << "-bits.\n"
            << std::endl;

  return EXIT_SUCCESS;
}