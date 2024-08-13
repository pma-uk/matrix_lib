'''
* Filename:		MyMatrix.py
* Project:		MatrixLib
* By:			Paul Ma
* Date:			August 13, 2024
* Description:  This Python script contains a Pythonic MyMatrix class to expose the functionality of Matrix in C++ to Python.
'''

import MatrixLib
import atexit


class LibraryManager:
    _initialized = False

    '''
    * Function:     setup
    *
    * Purpose:      Initializes the Matrix library if it has not already been initialized.
    *               This ensures that the library resources are properly managed and released.
    *
    * Inputs:       None
    *
    * Outputs:      None
    *
    * Returns:      None
    *
    * Throws:       Any exceptions raised by MatrixLib.setUpLibrary(), indicating issues
    *               during the initialization process. Ensure proper error handling when calling.
    '''
    @staticmethod
    def setup():
        if not LibraryManager._initialized:
            MatrixLib.setUpLibrary()
            atexit.register(MatrixLib.tearDownLibrary)
            LibraryManager._initialized = True


class MyMatrix:
    
    '''
    * Function:     __init__
    * Purpose:      Initializes a MyMatrix instance. Constructs the matrix using provided data or dimensions, or defaults to a configuration-based matrix.
    *
    * Inputs:       data        (Optional) A 2D list representing matrix data. If provided, it initializes the matrix using this data.
    *               rows        (Optional) Number of rows in the matrix. Used if data is not provided.
    *               cols        (Optional) Number of columns in the matrix. Used if data is not provided.
    *               initValue   (Optional) Initial value for all elements in the matrix. Used if rows and cols are provided.
    *
    * Outputs:      None
    *
    * Returns:      None
    *
    * Throws:       ValueError - If the provided data is invalid or causes an exception in the C++ layer.
    *               RuntimeError - If an error occurs in the C++ layer while initializing the matrix.
    '''
    def __init__(self, data=None, rows=None, cols=None, initValue=0.0):
        LibraryManager.setup()

        try:
            if data is not None:
                self.matrix = MatrixLib.Matrix(data)
            elif rows is not None and cols is not None:
                self.matrix = MatrixLib.Matrix(rows, cols, initValue)
            else:
                # Default constructor uses the config file
                self.matrix = MatrixLib.Matrix()
        except ValueError as e:
            print(f"ValueError: {e}")
            self.matrix = MatrixLib.Matrix([[]])  
            print("Initialized to an empty matrix due to ValueError.")
        except RuntimeError as e:
            print(f"RuntimeError: {e}")
            self.matrix = MatrixLib.Matrix([[]]) 
            print("Initialized to an empty matrix due to RuntimeError.")

    '''
    * Function:     __add__
    * Purpose:      Adds two MyMatrix instances by adding their underlying Matrix objects and returns a new MyMatrix instance.
    *
    * Inputs:       rhs     MyMatrix - The right-hand side MyMatrix to be added to the current instance.
    *
    * Outputs:      None
    *
    * Returns:      MyMatrix - A new MyMatrix instance containing the result of the addition.
    '''
    def __add__(self, rhs):
        result = self.matrix + rhs.matrix
        return MyMatrix(result.getMatrixData()) 

    '''
    * Function:     __str__
    * Purpose:      Provides a human-readable string representation of the MyMatrix instance.
    *
    * Inputs:       None
    *
    * Outputs:      None
    *
    * Returns:      str - A string representation of the matrix.
    '''
    def __str__(self):
        return self.matrix.toString()

    '''
    * Function:     __repr__
    * Purpose:      Provides a string representation of the MyMatrix instance suitable for the interactive interpreter.
    *
    * Inputs:       None
    *
    * Outputs:      None
    *
    * Returns:      str - A string representation of the matrix suitable for the interactive interpreter.
    '''
    def __repr__(self):
        return self.__str__()

# Example usage
if __name__ == "__main__":
    mat1 = MyMatrix([[3, 4, 5], [1, 4, 5], [0, 0, 0]])
    mat2 = MyMatrix()
    mat3 = MyMatrix(rows=3, cols=3, initValue=0.5)
    mat_res = mat1 + mat2 + mat3

    print(f"Matrix 1\n{mat1}")
    print(f"\nMatrix 2\n{mat2}")
    print(f"\nMatrix 3\n{mat3}")
    print(f"\nSum of matrices\n{mat_res}")