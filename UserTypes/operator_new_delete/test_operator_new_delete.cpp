/*!
 *  \file       test_operator_new_delete.cpp
 *  \brief
 *
 */


#include "test_operator_new_delete.hpp"

#include "operator_new_delete.hpp"
#include "class_specific_operator_new_delete.hpp"
#include "finally.hpp"

#include <iostream>
#include <cmath>
#include <cassert>

#define __CPP_SIZED_DEALLOCATION    1

const nothrow_t nothrow;

constexpr const int ARRAY_LENGTH = 10;

void UTest_CheckOrdinaryOperatorNewDelete()
{
    int* ptr = (int*)operator new(sizeof(int));

    *ptr = 125;

    operator delete(ptr);
}

void UTest_CheckOrdinaryOperatorNewDelete_Array()
{
    double* numbers = (double*)operator new[](ARRAY_LENGTH * sizeof(double));

    for (int index = 0; index < ARRAY_LENGTH; ++index)
    {
        *(numbers + index) = 3.1415926 + index + 1;
    }

    for (int index = 0; index < ARRAY_LENGTH; ++index)
    {
        std::cout << "numbers[" << index << "] = " << numbers[index] << ",  ";
        if ((index + 1) % 5 == 0)
        {
            std::cout << std::endl;
        }
    }

    operator delete[](numbers);
}

void UTest_CheckOperatorNewDelete_NoThrow()
{
    int* ptr = (int*)operator new(sizeof(int), nothrow);

    *ptr = 12345;

    operator delete(ptr, nothrow);
}

void UTest_CheckOperatorNewDelete_NoThrow_Array()
{
    struct Test
    {
        int     a;
        double  b;
    };

    Test* array = (Test*)operator new[](sizeof(struct Test) * ARRAY_LENGTH, nothrow);
    if (array == nullptr)
    {
        return;
    }

    for (int index = 0; index < ARRAY_LENGTH; ++index)
    {
        array[index] = Test{.a = index+1, .b = 3.1415926 + index + 1};
    }
    for (int i = 0; i < ARRAY_LENGTH; ++i)
    {
        std::cout << "array[" << i << "] = { .a = " << (array + i)->a << ", .b = " << (array + i)->b << " },  ";
        if ((i + 1) % 5 == 0)
        {
            std::cout << std::endl;
        }
    }

    operator delete[](array, nothrow);
}

void UTest_CheckOperatorNewDelete_Alignment()
{
    align_val_t alignment = static_cast<align_val_t>(alignof(long double));

    long double* circle_area = (long double*)operator new(sizeof(long double), alignment);

    *circle_area = std::atan(1.0) * 4 * std::pow(12.45, 2);
    std::cout << "The area of a circle is " << *circle_area << std::endl;

    operator delete(circle_area, alignment);
}

void UTest_CheckOperatorNewDelete_Alignment_NoThrow_Array()
{
    align_val_t alignment = static_cast<align_val_t>(alignof(float));

    float* area_array = (float*)operator new[](ARRAY_LENGTH * sizeof(float), alignment, nothrow);

    auto destroy = finally([&area_array, alignment]() {
        operator delete[](area_array, alignment, nothrow);
    });

    for (int index = 0; index < ARRAY_LENGTH; ++index)
    {
        area_array[index] = 4 * std::atan2(1.0, 1.0) * std::pow(index + 1, 2);
    }

    for (auto i = 0; i < ARRAY_LENGTH; ++i)
    {
        std::cout << "area_array[" << i << "] = " << *(area_array + i) << ",  ";
        if ((i+1) % 5 == 0)
        {
            std::cout << std::endl;
        }
    }
}

void UTest_CheckOperatorNewDelete_WithWrongAlignment()
{
    align_val_t alignment = static_cast<align_val_t>(alignof(int) + 1);

    int* number = (int*)operator new(sizeof(int), alignment, nothrow);

    auto deleter = finally([&number, alignment]() {
        if (number == nullptr)
        {
            return;
        }
        operator delete(number, alignment, nothrow);
    });

    if (number != nullptr)
    {
        *number = 12;
    }
}

void UTest_CheckPlacementNewDelete()
{
    int num = 10;

    std::cout << "Before placement new: " << std::endl;
    printf("num = %d,  &num = %p\n", num, &num);

    // Placement new changes the value of num from 10 to 100
    // int* pnum = new (&num) int{100};
    int* pnum = (int*)operator new(sizeof(int), &num);
    *pnum = 100;

    std::cout << "After placement new: " << std::endl;
    printf("num = %d,  &num = %p,  *pnum = %d,  pnum = %p\n", num, &num, *pnum, pnum);

    operator delete(pnum, &num);
}

Complex::Complex(double real, double imag) : m_real{real}, m_imag{imag}
{
    std::cout << "Constructor: Complex(" << m_real << ", " << m_imag << ")" << std::endl;
}

Complex::~Complex()
{
    std::cout << "Destructor: Complex(" << m_real << ", " << m_imag << ")" << std::endl;
}

double Complex::norm() const
{
    return std::sqrt(m_real * m_real + m_imag * m_imag);
}

void Complex::print()
{
    printf("| %f + %fi | = %f\n", m_real, m_imag, norm());
}

void Complex::set_real(double real)
{
    m_real = real;
}

void Complex::set_imag(double imag)
{
    m_imag = imag;
}

void UTest_CheckHowToDeleteMemoryAllocatedByPlacementNew()
{
    unsigned char buf[100];

    Complex* pcomplex = new Complex(4.2, 5.9);
    Complex* pcomplex_array = new Complex[2];

    pcomplex_array[0].set_real(1);
    pcomplex_array[0].set_imag(1);
    pcomplex_array[1].set_real(2);
    pcomplex_array[1].set_imag(2);

    // Using placement new
    Complex* placed_complex = (Complex*)operator new(sizeof(Complex), buf);

    auto deleter = finally([&]() {
        delete pcomplex;
        delete[] pcomplex_array;

        operator delete(placed_complex, buf);
    });

    // Use the object allocated and constructed by placement new
    pcomplex->print();

    pcomplex_array[0].print();
    pcomplex_array[1].print();

    placed_complex->set_real(-10);
    placed_complex->set_imag(10);
    placed_complex->print();

    // No delete: Explicitly call to destructor
    placed_complex->~Complex();
}

void UTest_WhenWillPlacementNewDeleteShowSegmentFault()
{
    // Fine
    int num = 10;
    int* pnum = &num;
    int* placement_pnum = new (pnum) int{99};
    std::cout << "*placement_pnum = " << *placement_pnum << std::endl;

    // Incorrect, because area could be an invalid address
    double* area;
    // double* placement_area = new (area) double{3.1415926};      // here will pop up the segmentation fault.

    // Fine
    void* void_pnum = &num;
    int* placement = new(void_pnum) int{56};
    std::cout << "*placement = " << *placement << std::endl;

    int elem = 12315;
    // int* placed_elem = new(elem) int{95596};     // Error as the elem is not an address
    int* placed_elem = new(&elem) int{95596};
    std::cout << "*placed_elem = " << *placed_elem << std::endl;
}

void UTest_CheckClassSpecificOperatorNewDelete()
{
    size_t size = sizeof(Employee);
    Employee* employee_ptr = (Employee*)Employee::operator new(size);

    Employee::operator delete(employee_ptr);
}

void UTest_CheckClassSpecificOperatorNewDelete_WithConstructorDestructor()
{
    Employee* pemployee = new Employee(12, "Frederique Hsu", "R&D Constraint-Solving group");

    std::cout << "Employee name: " << pemployee->Name() << std::endl;
    std::cout << "Department: " << pemployee->Department() << std::endl;

    delete pemployee;
}

void UTest_CheckClassSpecificOperatorNewDelete_Array()
{
    Employee* employee_array = new Employee[4];

    employee_array[0].ChangeDepartment("Geometry Modeling group");
    employee_array[1].ChangeDepartment("Cloud CAD dept.");
    employee_array[2].ChangeDepartment("Testing group");
    employee_array[3].ChangeDepartment("DevOps dept.");

    for (int index = 0; index < 4; ++index)
    {
        std::cout << "employee_array[" << index << "].department = "
                  << (employee_array + index)->Department() << std::endl;
    }

    delete [] employee_array;
}

void UTest_CheckClassSpecificPlacementNewDelete()
{
    constexpr const size_t size = sizeof(Employee);

    char buffer[10 * size];

    Employee* placed_employee = (Employee*)Employee::operator new(size, buffer);

    placed_employee->Id() = 15096;
    // placed_employee->Name().append("Konstantin");
    // placed_employee->ChangeDepartment("Russian Ledas counterpart");

    std::cout << "The placed employee: ID = " << placed_employee->Id()
              << ", Department = " << placed_employee->Department() << std::endl;

    Employee::operator delete(placed_employee, buffer);
}

void UTest_CheckClassSpecificOperatorNewDelete_WithAlignment()
{
    align_val_t alignment = static_cast<align_val_t>(alignof(Employee));

    Employee* aligned_employee = (Employee*)Employee::operator new(sizeof(Employee), alignment);

    aligned_employee->ChangeDepartment(std::string("Russian Ledas counterpart"));
    aligned_employee->Id() = 6950;

    std::cout << "The aligned employee: ID = " << aligned_employee->Id()
              << ", Department = " << aligned_employee->Department() << std::endl;

    Employee::operator delete(aligned_employee, alignment);
}