/*!
 *  \file       std_extension.hpp
 *  \brief
 *
 */


#include <algorithm>


namespace std_extension
{
template<class C> void sort(C& c);
template<class C, class P> void sort(C& c, P pred);
}



template<class C>
void std_extension::sort(C& c)
{
    using namespace std;

    sort(c.begin(), c.end());
}


template<class C, class P>
void std_extension::sort(C& c, P pred)
{
    std::sort(c.begin(), c.end(), pred);
}
