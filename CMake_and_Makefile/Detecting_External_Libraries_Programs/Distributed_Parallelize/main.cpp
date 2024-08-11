/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    std::cout << "The processor is " << processor_name
              << ", rank = " << world_rank
              << " out of " << world_size << " processors"
              << std::endl;

    // Finalize the MPI environment, no more MPI calls can be made after this.
    MPI_Finalize();

    return EXIT_SUCCESS;
}