/*
* Filename:		ConfigReader.cpp
* Project:		MatrixLib
* By:			Paul Ma
* Date:			August 12, 2024
* Description:  This source file contains method definitions for the ConfigReader class.
*/

#include "ConfigReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

/*
* Function:     ConfigReader::readMatrixConfig
* Purpose:      Attempts to open a configuration file and read default values for number of rows, number of columns, and initial values.
*
* Inputs:       const std::string&              filename       The name and path of the configuration file. 
*
* Outputs:      None
*
* Returns:      std::tuple<int, int, double>                   Tuple containing the number of rows, the number of columns, and the initial value, in that order.
*/
std::tuple<int, int, double> ConfigReader::readMatrixConfig(const std::string& filename) 
{
    // Open config file
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Failed to open config file: " + filename);
    }

    int rows = 0;
    int cols = 0;
    double initVal = 0.0;

    // Read config file
    std::string line;
    while (std::getline(file, line)) 
    {
        std::istringstream iss(line);
        std::string key;

        // Split key and value, then parse value
        if (std::getline(iss, key, '=')) 
        {
            std::string value;
            if (std::getline(iss, value)) 
            {
                if (key.find("rows") != std::string::npos) 
                {
                    rows = std::stoi(value);
                } 
                else if (key.find("columns") != std::string::npos) 
                {
                    cols = std::stoi(value);
                } 
                else if (key.find("initial_value") != std::string::npos) 
                {
                    initVal = std::stod(value);
                }
            }
        }
    }

    // Cleanup
    file.close();

    return std::make_tuple(rows, cols, initVal);
}