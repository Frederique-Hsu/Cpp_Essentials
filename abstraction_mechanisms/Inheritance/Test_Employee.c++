/*!
 *  \file       Test_Employee.c++
 *  \brief
 *
 */


#include "Employee.hpp"

#include <gtest/gtest.h>

TEST(UTest4Employee, AccessEmployeeManagerInheritance)
{
    auto fn = [](Manager mgr, Employee emp) {
        std::list<Employee*> elist{&mgr, &emp};

        EXPECT_EQ(elist.size(), 2);
    };

    Employee knuth("Donald", 'E', "Knuth");

    Manager hennessy("John", 'L', "Hennessy", 12);

    fn(hennessy, knuth);
}

TEST(UTest4Employee, ConversionBetweenBaseAndDerivedClasses)
{
    auto convert = [](Manager mgr, Employee emp) {
        Employee* emp_ptr = &mgr;

        // Manager* mgr_ptr = &emp;    // error: not every Employee is a Manager

        Manager* mgr_ptr = static_cast<Manager*>(emp_ptr);
        
        mgr_ptr->print();
    };

    Manager prof_hopcroft("John", 'E', "Hopcroft", 10);
    Employee kernighan("Brian", 'E', "Kernighan");

    convert(prof_hopcroft, kernighan);
}

TEST(UTest4Employee, CheckVirtualFunctionsWorkingMechanism)
{
    Employee tanenbaum("Andrew", 'S', "Tanenbaum");
    Employee stroustrup("Bjarne", ' ', "Stroustrup");
    Manager kernighan("Brian", 'W', "Kernighan", 12);
    Employee ritchie("Dannis", ' ', "Ritchie");
    Employee gray("Jim", ' ', "Gray");
    Manager aho("Afred", 'V', "Aho", 15);
    Manager hopcroft("John", 'E', "Hopcroft", 20);
    Employee ullman("Jeffrey", 'D', "Ullman");
    Employee silberschatz("Abraham", ' ', "Silberschatz");
    Manager stallings("William", ' ', "Stallings", 9);
    Employee knuth("Donald", 'E', "Knuth");
    Manager hennessy("John", 'L', "Hennessy", 30);
    Employee peterson("Larry", 'L', "Peterson");

    std::list<Employee*> employees{&tanenbaum,  &stroustrup,    &kernighan,     &ritchie,       &gray, 
                                   &aho,        &hopcroft,      &ullman,        &silberschatz,  &stallings, 
                                   &knuth,      &hennessy,      &peterson};
    print_list(employees);
}

