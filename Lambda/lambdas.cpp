/*!
 *  \file       lambdas.cpp
 *  \brief
 *
 */


#include "lambdas.hpp"

#include <algorithm>

void print_modulo(const std::vector<int>& vec, std::ostream& os, int m)
{
    using namespace std;
    os << "Call the ordinary print_module() function." << endl;
#if defined(USE_CLOSURE_OBJECT)
    for_each(begin(vec), end(vec), Modulo_print(os, m));
#else
    for_each(begin(vec), end(vec),
             [&os, m](int x)
             {
                if (x % m == 0)
                {
                    os << x << endl;
                }
             });
#endif
}

Modulo_print::Modulo_print(std::ostream& os, int m) : os(os), m(m)
{
}

void Modulo_print::operator()(int x) const
{
    os << "Call the ordinary functor: Module_print()." << std::endl;
    if (x % m == 0)
    {
        os << x << std::endl;
    }
}

void printModule(const std::vector<int>& vec, std::ostream& os, int m)
{
    class Module
    {
    public:
        Module(std::ostream& os, int m) : os(os), m(m)
        {
        }

        void operator()(int x) const
        {
            os << "Call the local class Module functor." << std::endl;
            if (x % m == 0)
            {
                os << x << std::endl;
            }
        }
    private:
        std::ostream& os;
        int m;
    };

    std::for_each(std::begin(vec), std::end(vec), Module(os, m));
}

void printAll(const std::map<std::string, int>& m, const std::string& label)
{
    using namespace std;

    cout << label << ":\n{" << endl;
    for_each(m.begin(),
             m.end(),
             [](const pair<string, int>& p)
             {
                 cout << p << endl;
             });
    cout << "}" << endl;
}
