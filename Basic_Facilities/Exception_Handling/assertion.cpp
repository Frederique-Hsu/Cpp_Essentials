/*!
 *  \file       assertion.cpp
 *  \brief
 *
 */



#include "assertion.hpp"

#include <sstream>

namespace Assert
{
    Error::Error(const std::string& str) : std::runtime_error(str)
    {
    }

    std::string compose(const char* file, const char* function, int line, const std::string& message)
    {
        std::ostringstream os("(");
        os << file << ", " << function << ", " << line << "): " << message;
        return os.str();
    }

    void dynamic(bool b, const std::string& s)
    {
        dynamic<true, Error>(b, s);
    }

    void dynamic(bool b)
    {
        dynamic<true, Error>(b);
    }
}
