// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// MatrixPricerAmerican.cpp
// Álvaro Sánchez de Carlos
// Description: this file contains the source code the MatrixPricerAmerican class

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "MatrixPricerAmerican.hpp""
#include "../Options/AmericanOption.hpp"


// Function to write data to a CSV file
void MatrixPricerAmerican::WriteCSV(const std::string& output_path, const std::vector<std::vector<std::string>>& output_matrix) const
{
    std::ofstream file(output_path);

    if (file.is_open())
    {
        if (m_configuration == "price")
        {
            file << "Option,Type,K,S,r,sigma,b,Price\n";
        }
        else if (m_configuration == "all")
        {
            file << "Option,Type,K,S,r,sigma,b,Price,NumericDelta, NumericGamma\n";
        }

        // Write data
        for (const auto& row : output_matrix)
        {
            for (size_t i = 0; i < row.size(); ++i)
            {
                file << row[i];
                if (i < row.size() - 1)
                {
                    file << ",";
                }
            }
            file << "\n";
        }

        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << output_path << std::endl;
    }

}

// Constructor with matrix of options
MatrixPricerAmerican::MatrixPricerAmerican(const std::vector<AmericanOption>& matrix, const bool& print, const std::string& configuration) :
    m_matrix(matrix),
    m_configuration(configuration),
    m_print(print)
{}

// Constructor with input file path
MatrixPricerAmerican::MatrixPricerAmerican(const std::string& input_path, const bool& print, const std::string& configuration) :
    m_configuration(configuration),
    m_print(print)
{
    std::ifstream file(input_path);
    std::string line;
    bool header = true;

    while (std::getline(file, line))
    {
        if (header) {
            header = false;
            continue;
        }

        std::istringstream ss(line);
        std::vector<std::string> row;
        std::string value;

        while (std::getline(ss, value, ','))
        {
            row.push_back(value);
        }
        m_matrix.push_back(AmericanOption(row[1], std::stod(row[2]), std::stod(row[3]), std::stod(row[4]), std::stod(row[5]),
            std::stod(row[6]), std::stoi(row[0])));
    }
}

// Copy constructor
MatrixPricerAmerican::MatrixPricerAmerican(const MatrixPricerAmerican& source) :
    m_matrix(source.m_matrix),
    m_configuration(source.m_configuration),
    m_print(source.m_print)
{}

// Assignment operator
MatrixPricerAmerican& MatrixPricerAmerican::operator=(const MatrixPricerAmerican& source)
{
    // Check for self assignment
    // Compare the address of the object with 
    // the address of its source object 
    if (this == &source)
        return *this;

    m_matrix = source.m_matrix;
    m_configuration = source.m_configuration;
    m_print = source.m_print;

    // Return the current object (the object pointed by this)
    return *this;
}

// Function to price the matrix of options
std::vector<std::vector<std::string>> MatrixPricerAmerican::Price(double const& h, const std::string& output_path) const
{
    std::vector<std::vector<std::string>> output_matrix;

    for (const auto& option : m_matrix)
    {
        std::vector<std::string> row = option.ConvertToVectorString();

        if (m_configuration == "price")
        {
            row.push_back(std::to_string(option.Price()));
        }
        else if (m_configuration == "all")
        {
            row.push_back(std::to_string(option.Price()));
            row.push_back(std::to_string(option.NumericDelta(h)));
            row.push_back(std::to_string(option.NumericGamma(h)));
        }

        output_matrix.push_back(row);
    }

    if (m_print)
    {
        for (const auto& row : output_matrix)
        {
            // Print each element of the option
            std::cout << "Option: " << row[0] << ", ";
            std::cout << "Type: " << row[1] << ", ";
            std::cout << "K: " << row[2] << ", ";
            std::cout << "S: " << row[3] << ", ";
            std::cout << "r: " << row[4] << ", ";
            std::cout << "sigma: " << row[5] << ", ";
            std::cout << "b: " << row[6] << "\n";

            // Print the calculated parameters
            if (m_configuration == "price")
            {
                std::cout << "Price: " << row[7] << "\n";
            }

            else if (m_configuration == "all")
            {
                std::cout << "Price: " << row[7] << ", ";
                std::cout << "NumericDelta: " << row[8] << ", ";
                std::cout << "NumericGamma: " << row[9] << ", ";
            }
        }
    }

    if (!output_path.empty()) WriteCSV(output_path, output_matrix);

    return output_matrix;
}
