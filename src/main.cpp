#include <iostream>
#include "Matrix.h"
#include "ConfigReader.h"

int main() 
{
    auto [rows, cols, initValue] = ConfigReader::readMatrixConfig("config.ini");
    std::cout << rows << " " << cols << " " << initValue << std::endl;

    std::cout << "Creating matrix 1" << std::endl;
    Matrix matrix1(0, 0, 0.0);
    std::cout << "Matrix 1:" << std::endl;
    std::cout << matrix1.toString() << std::endl;

    std::cout << "Creating matrix 2" << std::endl;
    Matrix matrix2({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    std::cout << "Matrix 2:" << std::endl;
    std::cout << matrix2.toString() << std::endl;

    std::cout << "Creating matrix 3" << std::endl;
    Matrix matrix3;
    std::cout << "Matrix 3:" << std::endl;
    std::cout << matrix3.toString() << std::endl;

    std::cout << "Summing matrices" << std::endl;
    Matrix result = matrix1 + matrix2 + matrix3;

    std::cout << "Result of Matrix 1 + Matrix 2 + Matrix 3:" << std::endl;
    std::cout << result.toString() << std::endl;


    return 0;
}