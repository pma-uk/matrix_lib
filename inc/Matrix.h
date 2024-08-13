/*
* Filename:		Matrix.h
* Project:		MatrixLib
* By:			Paul Ma
* Date:			August 13, 2024
* Description:  This header file contains a class definition for Matrix, with class members keeping track of column and row count
*               and operator overloading for addition operations between Matrix objects.
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdexcept>

class Matrix
{
private:
    int rows;   // Number of rows in matrix
    int cols;   // Number of columns in matrix
    std::vector<std::vector<double>> matrixData;    // Matrix data as nested vector

public:
    // Constructors
    Matrix();
    Matrix(int rows, int cols, double initValue);
    Matrix(const std::vector<std::vector<double>> &matrixData);

    // Getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    std::vector<std::vector<double>> getMatrixData() const { return matrixData; }    

    // Operator overloading
    Matrix operator+(const Matrix& rhsMatrix) const;

    // Display matrix for testing
    std::string toString() const;

};

#endif // MATRIX_H