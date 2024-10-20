/*!
 *  \file       test_interface_specialization.c++
 *  \brief      
 *  
 */


#include "interface_specialization.hpp"

#include <algorithm>
#include <catch2/catch_test_macros.hpp>


TEST_CASE("Make the unit testing for the interface template complex<T>", "[interface_template]")
{
    SECTION("Instantiate the ordinary complex<T>")
    {
        my::complex<int> origin;
        my::complex<int> unit_x_coord(1, 0);
        my::complex<int> unit_y_coord(0, 1);
        
        my::complex<int> ordinary(3, 4);
        CHECK(ordinary.real() == 3);    CHECK(ordinary.imag() == 4);
        
        my::complex<int> z(ordinary);
        CHECK(z.real() == ordinary.real());     CHECK(z.imag() == ordinary.imag());
        
        z = my::complex<int>(6, 8);
        CHECK(z.real() == 6);       CHECK(z.imag() == 8);
        
        ordinary = 10;
        CHECK(ordinary.real() == 10);   CHECK(ordinary.imag() == 10);
        
        z += 5;
        CHECK(z.real() == 11);   CHECK(z.imag() == 8);
    }
    
    SECTION("Convert the complex with different and compatible types")
    {
        my::complex<int> icompl(3, 4);
        my::complex<long> lcomp(icompl);
        CHECK(lcomp.real() == icompl.real());   CHECK(lcomp.imag() == icompl.imag());
        
        lcomp = my::complex<short>(10, 20);
        CHECK(lcomp.real() == 10);  CHECK(lcomp.imag() == 20);  CHECK(lcomp.real() != icompl.real());   CHECK(lcomp.imag() != icompl.imag());
        
        lcomp += my::complex(-5, -8);
        CHECK(lcomp.real() == 10 - 5);      CHECK(lcomp.imag() == 20 - 8);
    }

    SECTION("Instantiate the specialized complex<float>")
    {
        my::complex<float> specialized_complex(2.0F, 3.5F);
        my::complex<float> fcomplex(specialized_complex);
        CHECK(specialized_complex.real() == 2.0F);
        CHECK(specialized_complex.imag() == 3.5f);
        CHECK(fcomplex.real() == specialized_complex.real());
        CHECK(fcomplex.imag() == specialized_complex.imag());
        
        fcomplex = 15.0F;
        CHECK(fcomplex.real() == 15.0F);
        CHECK(fcomplex.imag() == 15.0F);
        
        specialized_complex += 5.0F;
        CHECK(specialized_complex.real() == 2.0F + 5.0F);
        CHECK(specialized_complex.imag() == 3.5F);
        
        fcomplex = my::complex<float>(-5.8F, -12.5F);
        CHECK(fcomplex.real() == -5.8F);
        CHECK(fcomplex.imag() == -12.5F);
        
        const my::complex<float> cfcomp(2.34F, -5.89045F);
        CHECK(cfcomp.real() == 2.34F);
        CHECK(cfcomp.imag() == -5.89045F);
    }
    
    SECTION("Instantiate the specialized complex<double>")
    {
        my::complex<double> dcompl(3.0, 4.0);
        CHECK(dcompl.real() == 3.0);
        CHECK(dcompl.imag() == 4.0);
        
        my::complex<float> fcompl(6.0F, 8.0F);        
        my::complex<long double> ldcompl(12.0L, 13.0000L);
        
        my::complex<double> dz(fcompl);
        CHECK(dz.real() == fcompl.real());
        CHECK(dz.imag() == 8.0);
        
        my::complex<double> dcompl_obj(ldcompl);
        CHECK(dcompl_obj.real() == 12.0);
        CHECK(dcompl_obj.imag() == 13.0000L);
    }
}


TEST_CASE("Make the unit testing for instance specialization")
{    
    class Generator
    {
    public:
        static std::vector<int> generateFibonacciNumbers(int count)
        {
            std::vector<int> fibonacci(count);
            fibonacci[0] = 1;
            fibonacci[1] = 1;
            for (auto index = 2U; index < fibonacci.size(); ++index)
            {
                fibonacci[index] = fibonacci[index-1] + fibonacci[index-2];
            }
            return fibonacci;
        }
        static std::vector<int> generateOdds(int count)
        {
            std::vector<int> odds;
            for (auto i = 1; i <= count; ++i)
            {
                odds.push_back(i * 2 + 1);
            }
            return odds;
        }
        static std::vector<int> generateEvens(int count)
        {
            std::vector<int> evens;
            for (auto i = 1; i <= count; ++i)
            {
                evens.push_back(i * 2);
            }
            return evens;
        }
    };
    
    SECTION("Instantiate N dimensional matrix")
    {
        Matrix<int, 4> matrix_with_4rows(5);
        
        Matrix<int, 0> scalar(10);
        
        Matrix<int, 1> array(15);
        
        Matrix<int, 2> matrix(3, 7);
        
        std::cout << "\nN-diemsnional Matrix : " << std::endl;
        auto fibonacci = Generator::generateFibonacciNumbers(matrix_with_4rows.totalCount());
        matrix_with_4rows.assign(fibonacci);
        matrix_with_4rows.showLayout();
        CHECK(matrix_with_4rows.totalCount() == 4 * 5);
        
        std::cout << "\nScalar : " << std::endl;
        scalar.showLayout();
        CHECK(scalar.totalCount() == 1);
        
        std::cout << "\nArray or Vector : " << std::endl;
        array.assign(Generator::generateOdds(array.totalCount()));
        array.showLayout();
        CHECK(array.totalCount() == 15);
        
        std::cout << "\n2D Matrix : " << std::endl;
        matrix.assign(Generator::generateEvens(matrix.totalCount()));
        matrix.showLayout();
        CHECK(matrix.totalCount() == 3 * 7);
    }
}