/*!
 *  \file       function_template_specialization.cpp
 *  \brief      
 *  
 */



#include <cstring>
#include <vector>

template<typename T> void sort(std::vector<T>& vec)
{
    const int n = static_cast<int>(vec.size());
    
    for (int gap = n/2; 0 < gap; gap /= 2)
    {
        for (int i = gap; i != n; ++i)
        {
            for (int j = i - gap; 0 <= j; j -= gap)
            {
                if (less(vec[j + gap], vec[j]))
                {
                    std::swap(vec[j], vec[j + gap]);
                }
            }
        }
    }
}

template<typename T> bool less(T a, T b)
{
    return a < b;
}

template<> bool less(const char* a, const char* b)
{
    return std::strcmp(a, b) < 0;
}



