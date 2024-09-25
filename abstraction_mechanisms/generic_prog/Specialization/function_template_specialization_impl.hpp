/*!
 *  \file       function_template_specialization.cpp
 *  \brief      
 *  
 */



#include <cstring>
#include <limits>

template<typename T> void sort(std::vector<T>& vec)
{
    const std::size_t n = vec.size();
    
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

template<> constexpr int max_value<int>()
{
    return std::numeric_limits<int>::max();
}

template<> constexpr char max_value<char>()
{
    return std::numeric_limits<char>::max();
}

template<> constexpr int* max_value<int*>()
{
    return std::numeric_limits<int*>::max();
}

template<> constexpr int const* max_value<int const*>()
{
    return std::numeric_limits<int const*>::max();
}

template<typename Iter> Iter my_algo(Iter p)
{
    auto x = max_value<typename Value_Type<Iter>::type>();
    return x;
}

template<typename Iter> Iter my_algo2(Iter p)
{
    auto x = Dummy::max2(typename Value_Type<Iter>::type{});
    return x;
}