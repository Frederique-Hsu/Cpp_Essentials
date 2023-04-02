/*!
 *  \file   Vector.hpp
 *  \brief  
 *  
 */


#pragma once

namespace CopyMove
{
    class Vector
    {
    private:
        double* elem;
        int sz;
    public:
        Vector(int s);      /* constructor */
        ~Vector();          /* destructor */

        Vector(const Vector& a);                /* copy constructor */
        Vector& operator=(const Vector& a);     /* copy assignment */

        Vector(Vector&& a);                 /* move constructor */
        Vector& operator=(Vector&& a);      /* move assignment */

        double& operator[](int i);
        const double& operator[](int i) const;

        int size() const;
    };

    Vector operator+(const Vector& a, const Vector& b);
}