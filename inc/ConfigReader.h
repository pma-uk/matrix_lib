/*
* Filename:		ConfigReader.h
* Project:		MatrixLib
* By:			Paul Ma
* Date:			August 12, 2024
* Description:  This header file contains a class definition for ConfigReader, with a static method for reading 
*               a config file with default initialization parameters for the Matrix class.
*/

#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <tuple>

class ConfigReader 
{
public:
    static std::tuple<int, int, double> readMatrixConfig(const std::string& filename);
};

#endif // CONFIG_READER_H