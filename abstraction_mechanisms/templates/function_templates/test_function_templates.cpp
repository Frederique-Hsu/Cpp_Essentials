/*!
 *  \file       test_function_templates.cpp
 *  \brief      
 *  
 */


#include "function_templates.hpp"

#include <gtest/gtest.h>


TEST(UTest4FunctionTemplates, CheckShellSort)
{   
    std::vector<int> numbers{8, 6, 475, 620, -46, -98, 91, 125, 6840, 1203, 951}; 
    
    #if false
    sort(numbers);
    #else
    shell_sort(numbers);
    #endif
    
    auto print = [](const std::vector<int>& nums) -> void
    {
        for (auto num : nums)
        {
            std::cout << num << "  ";
        }
        std::cout << std::endl;
    };
    
    print(numbers);
}


TEST(UTest4FunctionTemplates, CheckUserDefinedPredicate)
{    
    auto print = []<typename Container>(const Container& items)
    {
        for (auto item : items)
        {
            std::cout << item << ",  ";
        }
        std::cout << std::endl;
    };
    
    auto fn = [print](std::vector<int>& numbers, std::vector<std::string>& strings)
    {
        sort(numbers);
        std::cout << "升序排列：";
        print(numbers);
        shell_sort<int, std::greater<int>>(numbers);
        std::cout << "降序排列：";
        print(numbers);
        
        sort(strings);
        std::cout << "区分大小写升序排列：";
        print(strings);
        shell_sort<std::string, NoCaseComparator>(strings);
        std::cout << "不区分大小写升序排列：";
        print(strings);
    };
    
    std::vector<int> numbers{15, -515, 64, -54, -756, 1265, -648, 24, 954, -1265, 698, 159, 357};
    std::vector<std::string> strings{"Unfortunately", "the", "rulE", "thAT", "only", "trailing", "Template", "ARGuments",
        "can", "BE", "specified", "leads", "us", "to", "HAvE", "TO", "speciFY"};
    
    fn(numbers, strings);
}
    
namespace {
    template<typename T, int max>
    struct Buffer
    {
        friend T& lookup(Buffer<T, max>& buffer, const char* p)
        {
            for (int index = 0; index < max; ++index)
            {
                if (buffer.buf[index] == T{p})
                {
                    return buffer.buf[index];
                }
            }
            return buffer.buf[0];
        }
    private:
        T buf[max];
    public:
        Buffer();
        
        void assign(int index, const T& value);
        int getArrayLength() const;
    };
    
    template<typename T, int max>
    Buffer<T, max>::Buffer()
    {
        for (auto index = 0; index < max; ++index)
        {
            buf[index] = T{};
        }
    }
    
    template<typename T, int max>
    void Buffer<T, max>::assign(int index, const T& value)
    {
        if ((index < 0) or (index >= max))
        {
            std::string error_mesg = "The index = ";
            error_mesg += std::to_string(index) + " had exceeded the range.";
            throw std::out_of_range(error_mesg.c_str());
        }
        buf[index] = value;
    }
    
    template<typename T, int max>
    int Buffer<T, max>::getArrayLength() const
    {
        return sizeof(buf)/sizeof(T);
    }
        
    template<int max>
    auto& retrieve(Buffer<std::string, max>& buffer, const char* p)
    {
        return lookup(buffer, p);
    }
    
TEST(UTest4FunctionTemplates, DeduceFunctionTemplateArgument)
{
    Buffer<std::string, 16> string_buffers;
    string_buffers.assign(1, "I");
    string_buffers.assign(2, "love");
    string_buffers.assign(3, "you");
    string_buffers.assign(5, "Alice");
    string_buffers.assign(6, "Yu");
    string_buffers.assign(8, "I");
    string_buffers.assign(9, "want");
    string_buffers.assign(10, "to");
    EXPECT_THROW({ string_buffers.assign(16, "dummy"); }, std::out_of_range);
    EXPECT_EQ(string_buffers.getArrayLength(), 16);
    
    auto& word = retrieve(string_buffers, "Alice");
    EXPECT_EQ(word, "Alice");
}
}   // namespace


template<typename T>
T* create()
{
    return new T{};
}

template<typename T>
void destroy(T* ptr)
{
    delete ptr;
}

TEST(UTest4FunctionTemplates, ExplicitlySpecifyTemplateTypeArgument)
{
    std::vector<int> ivec;      // 类模板，类型实参为int
    EXPECT_EQ(typeid(ivec[0]), typeid(int));
    
    int* p = create<int>();     // 函数模板，实参为int
    EXPECT_EQ(typeid(p), typeid(int*));
    destroy(p);
    
    // int* q = create();          // Error: could not deduce the template parameter 'T'
}

template<typename T, typename U> void deduceType(const T, U (*fnptr)(U arg))
{
    std::cout << "The T type is " << typeid(T).name() << std::endl;
    std::cout << "The fnptr type is " << typeid(fnptr).name() << std::endl;
}

int access(int)
{
    return int{};
}

void highlight(const char* p)
{
    deduceType(p, access);      // OK: 可以进行类型推断， T 是 char, U 是 int
    // deduceType(p, highlight);   // Error: 不能推断U， 因为highlight函数的参数类型和返回类型与 U (*fnptr)(U arg) 不同
};

template<typename T> void fn(T value, T* pointer) {}

void gc(int number)
{
    fn(number, &number);        // Correct
    // fn(number, "Remember!");    // Error: 二义性： T被推断出到底是 int 还是 const char ?
}

TEST(UTest4FunctionTemplates, DeduceFunctionTemplateTypeArgument)
{
    highlight("deduce the type argument of a function template");
}