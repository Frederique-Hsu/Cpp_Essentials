/*!
 *  \file       static_dynamic_cast.cpp
 *  \brief
 *
 */


#include "static_dynamic_cast.hpp"

#include <iostream>

TEST(UTest4StaticVersusDynamicCast, CheckTheDifferenceBetweenStaticAndDynamicCast)
{
    Radio radio("radio message");

    static_versus_dynamic_cast(radio);
}

TEST(UTest4StaticVersusDynamicCast, CheckCastFromVoidPtrToObjectPtr)
{
    IStorable* ptr_radio = new Radio("radio");

#if false
    void* ptr = (void*)ptr_radio;   // Mandatorily convert from IStorable* to void* in the C-style
#else
    /*!
     *  \note   static_cast do the mandatory casting,
     *          do not make any checking for the type safety.
     */
    void* ptr = static_cast<void*>(ptr_radio);
#endif

    Radio* pradio = cast_from_void_ptr_to_object_ptr(ptr);
    pradio->communicate();

    std::cout << "\ntypeid(ptr_radio).name() = " << typeid(ptr_radio).name() << std::endl
              << "typeid(pradio).name() = " << typeid(pradio).name() << std::endl;
    CHECK(ptr_radio == pradio);

    delete ptr_radio;
}

TEST(UTest4StaticVersusDynamicCast, CheckCastObeyConstRules)
{
    auto fn = [](const Receiver* const_ptr_receiver)
    {
        Receiver* ptr_receiver = const_cast<Receiver*>(const_ptr_receiver);     // OK
        const Receiver* cptr_receiver = const_cast<const Receiver*>(ptr_receiver);  // OK

        CHECK(typeid(const_ptr_receiver).name() == typeid(cptr_receiver).name());
    };

    const Receiver* receiver_cptr = new Radio("recevier");
    fn(receiver_cptr);
    delete receiver_cptr;
}