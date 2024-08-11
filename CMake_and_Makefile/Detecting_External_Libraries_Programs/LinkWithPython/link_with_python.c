/*!
 *  \file       link_with_python.c
 *  \brief
 *
 */


#include <Python.h>

int main(int argc, char* argv[])
{
    Py_SetProgramName(argv[0]);
    Py_Initialize();

    PyRun_SimpleString("from time import time, ctime\n"
                       "print('Hello, Python and C hybrid programming world!')\n");
    Py_Finalize();

    return EXIT_SUCCESS;
}