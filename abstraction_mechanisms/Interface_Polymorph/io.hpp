/*!
 *  \file       io.hpp
 *  \brief
 *
 */


#pragma once

#include "io_object.hpp"

#define MULTIPLE_INHERITANCE    1
#define SINGLE_INHERITANCE      2
#define IO_CLASS_TEMPLATE       SINGLE_INHERITANCE

#if (IO_CLASS_TEMPLATE == MULTIPLE_INHERITANCE)
    template<class T>
    class IO : public T, public IOObject
    {
    public:
        IO(std::istream&);
        ~IO() = default;

    public:
        IO* clone() const override;
        static IOObject* new_io(std::istream& is);
    };
#elif (IO_CLASS_TEMPLATE == SINGLE_INHERITANCE)
    template<class T>
    class IO : public IOObject
    {
    public:
        IO(std::istream&);
        ~IO();
    private:
        T* ptr;
    public:
        IO* clone() const override;

        static IOObject* new_io(std::istream& is);
        T* get_ptr() const;
    };

    template<class T>
    T* get(IOObject* ptr_obj);
#endif

using IO_Circle = IO<Circle>;
using IO_Triangle = IO<Triangle>;

class Data
{
public:
    Data(std::istream& is) {}
    virtual ~Data() = default;
};
using IO_Data = IO<Data>;   // 封装了一个具体类型
using IO_Int = IO<int>;     // 封装了一个内置类型


#include "io_impl.hpp"