/*!
 * 	\file	get_cpp_info.cpp
 * 	\brief	Get some version information about newest C++ standard.
 *
 */

#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
	std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

	return 0;
}
