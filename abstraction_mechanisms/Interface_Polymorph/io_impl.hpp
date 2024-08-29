/*!
 *  \file       io_impl.hpp
 *  \brief
 *
 */


#if (IO_CLASS_TEMPLATE == MULTIPLE_INHERITANCE)
    template<class T>
    IO<T>::IO(std::istream& is) : T(is), IOObject()
    {
    }

    template<class T>
    IO<T>* IO<T>::clone() const
    {
        return new IO<T>(*this);
    }

    template<class T>
    IOObject* IO<T>::new_io(std::istream& is)
    {
        return new IO<T>(is);
    }
#elif (IO_CLASS_TEMPLATE == SINGLE_INHERITANCE)
    template<class T>
    IO<T>::IO(std::istream& is) : ptr(new T(is))
    {
    }

    template<class T>
    IO<T>::~IO()
    {
        if (ptr != nullptr)
        {
            delete ptr;
        }
    }

    template<class T>
    IO<T>* IO<T>::clone() const
    {
        return new IO<T>(*this);
    }

    template<class T>
    IOObject* IO<T>::new_io(std::istream& is)
    {
        return new IO<T>(is);
    }

    template<class T>
    T* IO<T>::get_ptr() const
    {
        return ptr;
    }

    template<class T>
    T* get(IOObject* ptr_obj)
    {
        if (IO<T>* ptr_io = dynamic_cast<IO<T>*>(ptr_obj))
        {
            return ptr_io->get_ptr();
        }
        return nullptr;
    }
#endif