/*!
 *  \file       test_users.c++
 *  \brief      
 *  
 */


#include "users.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(UTest4Users)

    void fn(Users* ptr_users)
    {
        // static_cast<std::set<Person>*>(ptr_users);  // error: 不允许访问private基类
        // dynamic_cast<std::set<Person>*>(ptr_users);     // error: 不允许对private基类进行转换

        // static_cast<Receiver*>(const_ptr_receiver);   // error: 不能强制去除const
        // dynamic_cast<Receiver*>(const_ptr_receiver);      // error: dynamic_cast不能强制移除const限定符
    }
    
    BOOST_AUTO_TEST_CASE(CheckCastObeyAccessControlRules)
    {        
        Users* ptr_users = new Users{Person("Alice", Person::Gender::Female, 40),
                                     Person("Bob", Person::Gender::Male, 30),
                                     Person("Charlie", Person::Gender::Male, 35)};
        fn(ptr_users);
        std::cout << *ptr_users << std::endl;
        
        delete ptr_users;
    }
BOOST_AUTO_TEST_SUITE_END()