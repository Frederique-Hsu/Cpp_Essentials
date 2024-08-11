# File name     : use_numpy.py
# Description   :
#
#


import numpy as np

def print_ones(rows, cols):
    A = np.ones(shape=(rows, cols), dtype=float)
    print(A)

    # we return the number of elements to verify that
    # the C++ code is able to receive the return values
    num_elements = rows * cols
    return num_elements;