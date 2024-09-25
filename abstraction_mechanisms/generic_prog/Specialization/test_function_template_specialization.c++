/*!
 *  \file       test_function_template_specialization.c++
 *  \brief      
 *  
 */


#include "function_template_specialization.hpp"

#include <iostream>
#include <iomanip>
#include <ios>

#include <catch2/catch_test_macros.hpp>

template<class Container>
class PrintContainer
{
public:
    static void printContainerElements(const Container& container)
    {
        for (auto elem : container)
        {
            std::cout << elem << "    ";
        }
        std::cout << std::endl;
    }
};

TEST_CASE("Make the unit testing for function template specialization topic", 
          "[function_template]")
{
    
    SECTION("Verify the user-defined function template sort<T>(std::vector<T>& vec)")
    {
        std::vector<int> numbers{54, -56, 88, 156, 94, 125, -785, 265};
        
        sort(numbers);
        PrintContainer<std::vector<int>>::printContainerElements(numbers);
        CHECK(numbers[0] == -785);
    }
    
    SECTION("Specialize the less<const char*>() edition")
    {
        std::vector<const char*> strings{"As", "written", "sort()", "will", "not", "sort", "a", "vector<char>", "correctly"};
        
        sort(strings);
        PrintContainer<std::vector<const char*>>::printContainerElements(strings);
        CHECK(strings.size() == 9);
    }
    
    SECTION("Specialize the function template, but it is not overloading")
    {
        auto int_max_value = max_value<int>();
        auto char_max_value = max_value<char>();
        auto int_const_pointer_max_value = max_value<int const*>();
        
        CAPTURE(int_max_value);
        CHECK(int_max_value == 0x7FFF'FFFF);
        CHECK(char_max_value == 0x7F);
        
        int* array = new int[5];
        array[0] = 0;
        array[1] = 1;
        array[2] = 2;
        array[3] = 3;
        array[4] = 4;
        
        int* iterator = my_algo(array);
        int* iterator2 = my_algo2(array + 2);
        CHECK(iterator == iterator2);
        CHECK(iterator == nullptr);
        
        delete [] array;
    }
}