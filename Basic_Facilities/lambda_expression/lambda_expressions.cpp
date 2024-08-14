/*!
 *  \file       lambda_expressions.cpp
 *  \brief
 *
 */


#include "lambda_expressions.hpp"

#include <algorithm>

#define USE_LAMBDA_EXPRESSION               1
#define USE_CLOSURE_OBJECT                  2
#define USE_LOCAL_CLASS_INSIDE_FUNCTION     3
#define USE_NAMED_LAMBDA                    4
#define INVOKATION_METHOD                   USE_NAMED_LAMBDA

/*!
 *  \brief      如果v[i] % m == 0, 则输出v[i]到os
 */
void print_modulo(const std::vector<int>& v, std::ostream& os, int m)
{
#if (INVOKATION_METHOD == USE_LAMBDA_EXPRESSION)
    std::cout << "Calling the edition of lambda expression:" << std::endl;
    std::for_each(std::begin(v),
                  std::end(v),
                  [&os, m](int x)
                  {
                      if (x % m == 0)
                      {
                          os << x << std::endl;
                      }
                  });
#elif (INVOKATION_METHOD == USE_CLOSURE_OBJECT)
    std::cout << "Calling the edition of closure object:" << std::endl;
    /*!
     *  \note   我们把由lambda生成的类的对象称为闭包对象 closure object，或者简称为闭包。
     *          此处的Modulo_print即为一个闭包对象。
     */
    std::for_each(std::begin(v),
                  std::end(v),
                  Modulo_print(os, m));
#elif (INVOKATION_METHOD == USE_LOCAL_CLASS_INSIDE_FUNCTION)
    std::cout << "Calling the edition of local class object:" << std::endl;
    class ModuloPrint
    {
    private:
        std::ostream& os;
        int m;
    public:
        ModuloPrint(std::ostream& os, int m) : os(os), m(m)
        {
        }
        void operator()(int x) const
        {
            if (x % m == 0)
            {
                os << x << std::endl;
            }
        }
    };

    std::for_each(v.begin(), v.end(), ModuloPrint(os, m));
#elif (INVOKATION_METHOD == USE_NAMED_LAMBDA)
    std::cout << "Calling the edition of named lambda object:" << std::endl;
    auto Modulo_Print = [&os, m](int x) {
        if (x % m == 0)
        {
            os << x << std::endl;
        }
    };

    std::for_each(std::begin(v), std::end(v), Modulo_Print);
#else
    std::cout << "Calling the edition of traditional method:" << std::endl;
    for (auto& elem : v)
    {
        if (elem % m == 0)
        {
            os << elem << std::endl;
        }
    }
#endif
}


Modulo_print::Modulo_print(std::ostream& os, int m) : os(os), m(m)
{
}

void Modulo_print::operator()(int x) const
{
    if (x % m == 0)
    {
        os << x << std::endl;
    }
}

void algo(std::vector<int>& v)
{
    std::sort(v.begin(), v.end());

    std::sort(v.begin(),
              v.end(),
              [](int x, int y)
              {
                  return std::abs(x) < std::abs(y);
              });
}

void algo(std::vector<int>& vec, bool sensitive)
{
    std::sort(vec.begin(),
              vec.end(),
              [sensitive](int x, int y)
              {
                  /*!
                   *    \warning    Variable 'sensitive' cannot be implicitly captured in a lambda
                   *                with no capture-default specified.
                   */
                  return sensitive ? (x < y) : (std::abs(x) < std::abs(y));
              });
}
