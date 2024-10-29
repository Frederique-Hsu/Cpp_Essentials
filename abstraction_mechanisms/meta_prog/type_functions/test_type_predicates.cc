/*!
 *  \file       test_type_predicates.cc
 *  \brief
 *
 */


#include "type_predicates.hpp"

#include <boost/test/unit_test.hpp>

#include <cstdint>
#include <vector>
#include <iomanip>
#include <ios>


BOOST_AUTO_TEST_SUITE(UTest4TypePredicates)

    BOOST_AUTO_TEST_CASE(CheckCopy)
    {
        int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int array[15] = {0x00};

        copy(array, numbers, 8);

        std::string letters[] = {"ABCDE", "FGHIJ", "KLMN", "OPQRST"};
        std::string dest_str[5];

        copy<std::string>(dest_str, letters, 3);
        for (auto index = 0U; index < sizeof(dest_str)/sizeof(dest_str[0]); ++index)
        {
            std::cout << dest_str[index] << std::endl;
        }
    }

    BOOST_AUTO_TEST_CASE(CheckUserDefinedTypePredicates)
    {
        BOOST_CHECK(Estd::Is_Pod<int>() == true);

        struct Vec3D
        {
            int x_coord;
            int y_coord;
            int z_coord;
        };
        BOOST_CHECK(Estd::Is_Pod<Vec3D>() == true);

        struct I2C
        {
            int start_bit : 1;
            int address_bit : 7;
            int read_write : 1;
            int addr_ack_bit : 1;
            int data_frame : 8;
            int data_ack_bit : 1;
            int stop_bit : 1;
        };

        std::cout << "sizeof(I2C) = " << sizeof(I2C) << std::endl;

        BOOST_CHECK(Estd::Is_Pod<I2C>() == true);
    }

    BOOST_AUTO_TEST_CASE(CheckComplexUserDefinedType)
    {
        struct CAN_Frame
        {
            std::uint64_t SOF               :  1;   // Start of frame
            std::uint64_t ID                : 11;   // Identifier
            std::uint64_t RTR               :  1;   // Remote transmit request
            std::uint64_t IDE               :  1;   // Identifier extension
            std::uint64_t r0                :  1;   // Reserved bit0
            std::uint64_t DLC               :  4;   // Data length code
            // std::uint8_t  DataFields[0]          // Data fields should at this position originally
            std::uint64_t CRC_Seq           : 15;   // CRC Sequence
            std::uint64_t CRC_DEL           :  1;   // CRC Delimiter
            std::uint64_t ACK               :  1;   // Acknowledge
            std::uint64_t ACK_DEL           :  1;   // Ack. Delimiter
            std::uint64_t EoFrame           :  7;   // End of frame
            std::uint8_t  DataFields[0]         ;   // Data fields, at most 8 bytes, determined by DLC.
        };

        std::cout << "sizeof(CAN_Frame) = " << sizeof(CAN_Frame) << std::endl;
        BOOST_CHECK(Estd::Is_Pod<CAN_Frame>() == true);
    }

/*============================================================================*/

    template<typename T, int ROW, int COL>
    class Matrix
    {
    public:
        Matrix() = default;
    private:
        T matrix[ROW][COL];
    public:
        void assign(const std::vector<T>& init_list);
        void print();
    };

    BOOST_AUTO_TEST_CASE(CheckObjHolderTypePredicated)
    {
        Obj_Holder<Matrix<int, 15, 10>> matrix_holder;

        auto generateFibonacci = [](int count)
        {
            if (count <= 2)
            {
                return std::vector<int>();
            }
            std::vector<int> fibonacci(count);
            fibonacci[0] = 1;
            fibonacci[1] = 1;
            for (int index = 2; index < count; ++index)
            {
                fibonacci[index] = fibonacci[index-1] + fibonacci[index-2];
            }
            return fibonacci;
        };
        matrix_holder->assign(generateFibonacci(45));
        matrix_holder->print();
    }

    template<typename T, int ROW, int COL>
    void Matrix<T, ROW, COL>::assign(const std::vector<T>& vec)
    {
        int index = 0;
        for (T elem : vec)
        {
            if (index >= ROW * COL)
            {
                break;
            }
            matrix[index / COL][index % COL] = elem;
            index++;
        }
    }

    template<typename T, int ROW, int COL>
    void Matrix<T, ROW, COL>::print()
    {
        using namespace std;
        cout << setw(8) << left << " " << setw(4) << " ";
        for (int col_index = 0; col_index < COL; ++col_index)
        {
            cout << setw(12) << right << string("col. #" + std::to_string(col_index+1)) << setw(4) << " ";
        }
        cout << endl;

        for (int row_index = 0; row_index < ROW; ++row_index)
        {
            cout << setw(8) << left << string("row #" + to_string(row_index+1)) << setw(4) << " ";
            for (int col_index = 0; col_index < COL; ++col_index)
            {
                cout << setw(12) << right << matrix[row_index][col_index] << setw(4) << " ";
            }
            cout << endl;
        }
    }

/*============================================================================*/

    BOOST_AUTO_TEST_CASE(SelectingFunction)
    {
        struct X
        {
            void operator()(int x)
            {
                std::cout << "X(" << x << ")" << std::endl;
            }
        };

        struct Y
        {
            void operator()(int y)
            {
                std::cout << "Y(" << y << ")" << std::endl;
            }
        };

        auto fn = []()
        {
            Conditional<(sizeof(int) > 4), X, Y>{}(5);

            using ZType = Conditional<Estd::Is_Polymorphic<X>(), X, Y>;
            ZType zobj;
            zobj(7);
        };

        fn();
    }

BOOST_AUTO_TEST_SUITE_END()