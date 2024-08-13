%module MatrixLib

// Include headers
%{
    #include "Matrix.h"
    #include "ConfigReader.h"
    #include "LibSetup.h"
    #include <vector>
%}

%include "std_vector.i"
%include "std_string.i"
%include "exception.i"

// For exception handling
%exception 
{
    try 
    {
        $action;
    } 
    catch (const std::invalid_argument &e) 
    {
        PyErr_SetString(PyExc_ValueError, e.what());
    } 
    catch (const std::runtime_error &e) 
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
    } 
    catch (const std::exception &e) 
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
    }
}

// For passing lists and nested lists from Python to C++
%template(VectorOfDouble) std::vector<double>;
%template(VectorOfStructVector) std::vector<std::vector<double> >;

// Expose class and methods to Python
%newobject Matrix::toString;

%include "Matrix.h"
%include "LibSetup.h"

