/*!
 *  \file       static_polymorphism.hpp
 *  \brief      
 *  
 */


#pragma once


namespace static_polymorphism
{
    /*!
     *  \note   CRTP (curiously recurring template pattern) is a method which can be seen as 
     *          a static polymorphism.
     */
    template<typename T> class base     /* templated base class */
    {
    public:
        void doWork();      /*!< \note  no virtual function here */
    };

    class derived : public base<derived>
    {
    public:
        /*!
         *  Declare base as friend, so doWorkImpl() can be called. 
         *  because we still want to call the base class method.
         */
        friend class base<derived>;
        void doWorkImpl();
    };

    template<typename T>
    void base<T>::doWork()
    {
        /*!
         *  \attention  we cast this to the template type, where the actual implementation lives.
         */
        static_cast<T*>(this)->doWorkImpl();
    }

/*================================================================================================*/

    /*!
     *  We create a concept 'can_work' to check whether doWork() is implemented,
     *  this will describe our interface.
     */
    template<typename T>
    concept can_work = requires(T t)
    {
        t.doWork();
    };

    /*!
     *  now we apply this concept to an empty type, which represents a worker 
     *  (or our base class)
     */
    template<can_work T>
    class worker : public T
    {
    };

    /*!
     *  now create a concrete worker (corresponding derived) where we implement the doWork()
     */
    class concrete_worker
    {
    public:
        void doWork();
    };
    /*! an alias for our concept worker */
    using my_worker = worker<concrete_worker>;
}