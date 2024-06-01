/*!
 *  \file       lambdas.hpp
 *  \brief
 *
 */


#pragma once

#include <vector>
#include <iostream>
#include <map>

/*!
 *  \section    Prototypes
 */
void print_modulo(const std::vector<int>& vec, std::ostream& os, int m);

template<typename Container> void print_modulo(const Container& container, std::ostream& os, int m);

void printModule(const std::vector<int>& vec, std::ostream& os, int m);

template<class Container> void printModulo(const Container& container, std::ostream& os, int m);

template<typename... VarType> void algo(int s, VarType... var);

template<typename U, typename V> std::ostream& operator<<(std::ostream& os, const std::pair<U, V>& p);

void printAll(const std::map<std::string, int>& m, const std::string& label);

class Modulo_print
{
public:
    Modulo_print(std::ostream& os, int m);
    template<typename Container> void operator()(Container container) const;
    void operator()(int x) const;
private:
    std::ostream& os;
    int m;
};

/*================================================================================================*/

/*!
 *  \section    Implementations
 */
template<typename Container>
void Modulo_print::operator()(Container container) const
{
    os << "Call the functor template: Modulo_print<Container>()." << std::endl;
    for (auto iter = std::begin(container); iter != std::end(container); ++iter)
    {
        if (*iter % m == 0)
        {
            os << *iter << std::endl;
        }
    }
}

template<typename Container>
void print_modulo(const Container& container, std::ostream& os, int m)
{
    using namespace std;
    os << "Call the function template print_module<Container>()." << endl;
    for_each(begin(container), end(container),
             [&os, m](auto x)
             {
                if (x % m == 0)
                {
                    os << x << endl;
                }
             });
}

template<class Container>
void printModulo(const Container& container, std::ostream& os, int m)
{
    for (auto elem : container)
    {
        if (elem % m == 0)
        {
            os << elem << std::endl;
        }
    }
}

template<typename... VarType>
int h1(VarType... /* v */)
{
    return 1;
}

template<typename... VarType>
int h2(VarType... /* v */)
{
    return 2;
}

template<typename... VarType>
void algo(int s, VarType... var)
{
    auto helper = [&s, &var...]() {     // 捕获可变参数模板实参
        return s * (h1(var...) + h2(var...));
    };

    helper();
}

template<typename U, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<U, V>& p)
{
    return os << '{' << p.first << ", \t " << p.second << '}';
}
