/*
* Filename:		Matrix.cpp
* Project:		MatrixLib
* By:			Paul Ma
* Date:			August 12, 2024
* Description:  This source file contains method definitions for the Matrix class, which represents a 2D matrix and provides various operations
*               such as initialization, addition, and output to string format. Includes constructors for creating matrices with
*               configurations read from a file or directly from input parameters, as well as an overloaded '+' operator for matrix addition.
*               Note that this is a naive implementation of a matrix, not accounting for sparse matrices or other optimizations.
*/

#include "Matrix.h"
#include "ConfigReader.h"

#include <iostream>
#include <sstream>


// Matrix Constructors

/*
* Function:     Matrix::Matrix
* Purpose:      Default constructor that initializes the matrix with dimensions and initial values read from a configuration file.
*
* Inputs:       None
*
* Outputs:      None
*
* Returns:      None
*
* Notes:
*   - Uses ConfigReader to read matrix configuration from "config.ini".
*/
Matrix::Matrix()
{
    try 
    {
        auto [rows, cols, initValue] = ConfigReader::readMatrixConfig("config.ini");
        this->rows = rows;
        this->cols = cols;
        this->matrixData = std::vector<std::vector<double>>(rows, std::vector<double>(cols, initValue));
    } 
    catch (const std::runtime_error& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;

        throw;
    }
    catch (...) 
    {
        std::cerr << "An unexpected error occurred while reading the matrix configuration." << std::endl;

        throw;
    }
}


/*
* Function:     Matrix::Matrix
* Purpose:      Parameterized constructor to initialize the matrix with specified dimensions and an initial value.
*
* Inputs:       int     rows        Number of rows in the matrix.
*               int     cols        Number of columns in the matrix.
*               double  initValue   Initial value for all elements in the matrix.
*
* Outputs:      None
*
* Returns:      None
*
* Throws:       std::invalid_argument - If number of rows or columns is not a positive integer.
*/
Matrix::Matrix(int rows, int cols, double initValue) : rows(rows), cols(cols) 
{
    if (rows < 1 || cols < 1) 
    {
        throw std::invalid_argument("Number of rows and columns must be greater than 0");
    }

    matrixData.resize(rows, std::vector<double>(cols, initValue));
}

/*
* Function:     Matrix::Matrix
* Purpose:      Constructor that initializes the matrix from a 2D vector and validates the matrix data to ensure consistency.
*
* Inputs:       const std::vector<std::vector<double>> &matrixData - 2D vector containing matrix data.
*
* Outputs:      None
*
* Returns:      None
*
* Throws:       std::invalid_argument - If matrixData is empty or if rows have inconsistent column sizes.
*/
Matrix::Matrix(const std::vector<std::vector<double>>& matrixData) : matrixData(matrixData), rows(matrixData.size()) 
{
    if (this->rows == 0) 
    {
        throw std::invalid_argument("Matrix cannot be empty");
    }

    this->cols = matrixData[0].size();
    
    // Check that all rows have the same number of columns
    for (const auto &row : matrixData) 
    {
        if (row.size() != this->cols) 
        {
            throw std::invalid_argument("Inconsistent number of columns in matrix rows");
        }
    }
}


// '+' Operator Overloading

/*
* Function:     Matrix::operator+
* Purpose:      Overloaded '+' operator to add two matrices of the same dimensions and return the result as a new matrix.
*
* Inputs:       const Matrix& rhsMatrix - The matrix to be added to the current matrix.
*
* Outputs:      None
*
* Returns:      Matrix - A new matrix that is the result of the addition of the current matrix and rhsMatrix.
*
* Throws:       std::invalid_argument - If the dimensions of the two matrices do not match.
*/
Matrix Matrix::operator+(const Matrix& rhsMatrix) const 
{
    if (this->rows != rhsMatrix.rows || this->cols != rhsMatrix.cols) 
    {
        throw std::invalid_argument("Matrix dimensions do not match.");
    }

    Matrix result(this->rows, this->cols, 0.0);

    // Add element-wise
    for (int i = 0; i < this->rows; ++i) 
    {
        for (int j = 0; j < this->cols; ++j) 
        {
            result.matrixData[i][j] = this->matrixData[i][j] + rhsMatrix.matrixData[i][j];
        }
    }

    return result;
}


// For Displaying

/*
* Function:     Matrix::toString
* Purpose:      Converts the matrix to a string representation with elements separated by spaces and rows separated by newlines.
*
* Inputs:       None
*
* Outputs:      None
*
* Returns:      std::string - A string representation of the matrix, formatted with elements separated by spaces and rows by newlines.
*/
std::string Matrix::toString() const {
    std::ostringstream oss;

    for (size_t i = 0; i < matrixData.size(); ++i) 
    {
        for (const auto& elem : matrixData[i]) 
        {
            oss << elem << " ";
        }

        // Add newline only if it's not the last row
        if (i < matrixData.size() - 1) 
        {
            oss << "\n";
        }
    }

    return oss.str();
}