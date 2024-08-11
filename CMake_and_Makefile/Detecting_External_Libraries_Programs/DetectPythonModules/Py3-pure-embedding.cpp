/*!
 *  \file       Py3-pure-embedding.cpp
 *  \brief      Demonstrate how the C++ code to execute the external Python script.
 *
 */


#include <cstdlib>
#include <Python.h>
#include <iostream>


int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0]
                  << " python_file python_function_name [args]\n"
                  << std::endl;
        return EXIT_FAILURE;
    }

    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");

    PyObject* pName = PyUnicode_DecodeFSDefault(argv[1]);
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (pModule != nullptr)
    {
        PyObject* pFunc = PyObject_GetAttrString(pModule, argv[2]);
        if (pFunc && PyCallable_Check(pFunc))
        {
            PyObject* pValue;
            PyObject* pArgs = PyTuple_New(argc - 3);
            for (int i = 0; i < argc - 3; ++i)
            {
                pValue = PyLong_FromLong(std::atoi(argv[i+3]));
                if (!pValue)
                {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    std::cerr << "Cannot convert argument" << std::endl;
                    return EXIT_FAILURE;
                }
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != nullptr)
            {
                std::cout << "Result of call: " << PyLong_AsLong(pValue) << std::endl;
                Py_DECREF(pValue);
            }
            else
            {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                std::cerr << "Call failed!" << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (PyErr_Occurred())
            {
                PyErr_Print();
            }
            std::cerr << "Cannot find function \"" << argv[2] << "\"" << std::endl;
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else
    {
        PyErr_Print();
        std::cerr << "Failed to load \"" << argv[1] << "\"" << std::endl;
        return EXIT_FAILURE;
    }


    Py_Finalize();

    return EXIT_SUCCESS;
}