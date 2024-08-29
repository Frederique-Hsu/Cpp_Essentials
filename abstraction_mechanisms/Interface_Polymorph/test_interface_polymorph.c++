/*!
 *  \file       test_interface_polymorph.c++
 *  \brief
 *
 */


#include <boost/test/unit_test.hpp>

#include "io.hpp"

BOOST_AUTO_TEST_SUITE(UTest_InterfacePolymorph)

    void user()
    {
        std::cout << "Please enter one of these field: \"IO_Circle\", \"IO_Triangle\" "
                     "to indicate to create the corresponding object."
                  << std::endl;

        std::string field;        
        std::unique_ptr<IOObject> ioobj{get_obj(std::cin, field)};

        Shape* ptr_shape = nullptr;
        if (field == "IO_Circle")
        {
            ptr_shape = get<Circle>(ioobj.get());
        }
        else if (field == "IO_Triangle")
        {
            ptr_shape = get<Triangle>(ioobj.get());
        }
        else
        {
            ptr_shape = get<Shape>(ioobj.get());
        }
        
        if (ptr_shape)
        {
            ptr_shape->draw();
        }
        else
        {
            throw std::bad_cast();
        }
    }
    
    BOOST_AUTO_TEST_CASE(CheckHowInterfacePolymorphWorks)
    {
        // BOOST_CHECK_NO_THROW(user());
        // BOOST_CHECK_THROW(user(), std::bad_cast);
    }

BOOST_AUTO_TEST_SUITE_END()