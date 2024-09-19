/*!
 *  \file       function_templates_impl.hpp
 *  \brief      
 *  
 */



template<typename T>
void sort(std::vector<T>& numbers)      // Shell sorting
{
    const std::size_t n = numbers.size();
    
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            for (int j = i - gap; j >= 0; j -= gap)
            {
                if (numbers[j + gap] < numbers[j])
                {
                #if false
                    T temp = numbers[j];
                    numbers[j] = numbers[j + gap];
                    numbers[j + gap] = temp;
                #else
                    std::swap(numbers[j], numbers[j + gap]);
                #endif
                }
            }
        }
    }
}

template<typename T, typename Comparator> 
void shell_sort(std::vector<T>& numbers)
{
    Comparator comp;
    const std::size_t n = numbers.size();
    
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            for (int j = i - gap; j >= 0; j -= gap)
            {
                if (comp(numbers[j + gap], numbers[j]))
                {
                    std::swap(numbers[j], numbers[j + gap]);
                }
            }
        }
    }
}

template<typename T1, typename T2> std::pair<T1, T2> make_pair(T1 a, T2 b)
{
    return std::pair<T1, T2>{.first = a, .second = b};
}