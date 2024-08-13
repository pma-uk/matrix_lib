# MatrixLibrary

This project contains the implementation for Activity 1 of the Wells Fargo Job Demonstration. The task involves creating a Python wrapper for a simple C++ Matrix library using SWIG. The project involves the following:

- A C++ `Matrix` class with basic functionalities like construction and element-wise addition.
- Dummy `setUpLibrary()` and `tearDownLibrary()` functions for library initialization and cleanup.
- A Python wrapper using SWIG to the `Matrix` C++ library.
- A Python package that can be used to expose the C++ `Matrix` class in Python, with test code for demonstration purposes.

Project was developed and run on Ubuntu Linux version 24.04.

## Prerequisites

Ensure that the following packages are installed on your system:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake swig python3-dev
```

## Configuration File

The default constructor of the `Matrix` class reads its parameters (number of rows, number of columns, and initial value) from a configuration file named `config.ini`. The file should be located in the root directory of the project, or in the current working directory (CMake will copy this file to the `build` and `python` directories). 

Here is an example `config.ini` file:

```ini
[matrix]
rows = 3
columns = 3
initial_value = 0.0
```

## Compiling and building the project

Instructions for compiling and building the project, assuming you are in the project root directory `MatrixLib`:

```bash
cd build
cmake ..
make
export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
export PYTHONPATH=$(pwd):$PYTHONPATH
```

The Python package can be found in the `python` directory. In order to run a short demonstration, from the project root directory `MatrixLib`:

```bash
cd python
python3 MyMatrix.py
```

Alternatively, navigate to the `python` directory and start an interactive Python interpreter session:

```python
from MyMatrix import MyMatrix

# For example
mat = MyMatrix([[1,2,3],[4,5,6]])
mat + mat
```

## Answers to Step 3 questions

### a.  Explain how the wrapper is updated when the library is modified.

When the C++ library is updated (e.g., new methods or headers are added), the SWIG interface file (`Matrix.i`) should be updated accordingly to include the new methods or define any new mappings or templates that may be required. The wrapper should be rebuilt by re-running `cmake` and `make`. Barring any significant changes, `CMakeLists.txt` can remain unmodified.

### b.  Explain where the setUpLibrary() and tearDownLibrary() functions would be executed.

The `setUpLibrary()` function would most likely be called when the Python module is first imported to initialize any necessary resources. In this implementation, `setUpLibrary()` is executed during the first instantiation of a MyMatrix object.s

The `tearDownLibrary()` function would be called at the end of program execution to clean up resources or perform any other final steps before being unloaded by the OS. In this implementation, the function is registered to run automatically upon program termination using `atexit`.

### c.	Explain the memory management strategy.

The memory management strategy here relies heavily on SWIG's automatic memory management features, exception handling, and standard library support. This is particularly the case as no manual memory allocation was used in the C++ implementation, as the primary reliance was on STL containers.

In most cases, SWIG automatically manages the transfer of ownership between C++ and Python. When a Python object that wraps a C++ object is garbage collected, SWIG arranges for the appropriate C++ destructor to be called, freeing the memory allocated for that C++ object as well.

In specific cases, directives like `%newobject` inform SWIG that it is responsible for managing the lifecycle of objects that need explicit deallocation (in this case, for the allocated string object returned by the `Matrix::toString` method) and indicates that the caller (Python) should assume ownership of the returned object and ensure its deallocation.


## Author
Paul Ma

## Date
August 13, 2024