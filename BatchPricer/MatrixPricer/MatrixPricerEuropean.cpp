// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// MatrixPricerEuropean.cpp
// Álvaro Sánchez de Carlos
// Description: this file contains the source code the MatrixPricerEuropean class

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Options/EuropeanOption.hpp"
#include "MatrixPricerEuropean.hpp"

// Function to write data to a CSV file
void MatrixPricerEuropean::WriteCSV(const std::string& output_path, const std::vector<std::vector<std::string>>& output_matrix) const
{
    std::ofstream file(output_path);

    if (file.is_open())
    {
        if (m_configuration == "price")
        {
            file << "Option,Type,T,K,S,r,sigma,b,Price\n";
        }
        else if (m_configuration == "basic")
        {
            file << "Option,Type,T,K,S,r,sigma,b,Price,PricePutCallParity,Delta,Gamma,Vega,Theta,Rho\n";
        }
        else if (m_configuration == "all")
        {
            file << "Option,Type,T,K,S,r,sigma,b,Price,PricePutCallParity,Delta,Gamma,Vega,Theta,Rho,Vanna,Charm,Speed,Color,DvegaDtime, Vomma,Veta,Zomma,Lambda,Ultima\n";
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
MatrixPricerEuropean::MatrixPricerEuropean(const std::vector<EuropeanOption>& matrix, const bool& print, const std::string& configuration) :
    m_matrix(matrix),
    m_configuration(configuration),
    m_print(print)
{}

// Constructor with input file path
MatrixPricerEuropean::MatrixPricerEuropean(const std::string& input_path, const bool& print, const std::string& configuration) :
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

        m_matrix.push_back(EuropeanOption(std::string(row[1]), std::stod(row[2]), std::stod(row[3]), std::stod(row[4]),
            std::stod(row[5]), std::stod(row[6]), std::stoi(row[0]), std::stod(row[7])));
    }
}

// Copy constructor
MatrixPricerEuropean::MatrixPricerEuropean(const MatrixPricerEuropean& source) :
    m_matrix(source.m_matrix),
    m_configuration(source.m_configuration),
    m_print(source.m_print)
{}

// Assignment operator
MatrixPricerEuropean& MatrixPricerEuropean::operator=(const MatrixPricerEuropean& source)
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
std::vector<std::vector<std::string>> MatrixPricerEuropean::Price(const std::string& output_path) const
{
    std::vector<std::vector<std::string>> output_matrix;

    for (const auto& option : m_matrix)
    {
        std::vector<std::string> row = option.ConvertToVectorString();

        if (m_configuration == "price")
        {
            row.push_back(std::to_string(option.Price()));
        }
        else if (m_configuration == "basic")
        {
            row.push_back(std::to_string(option.Price()));
            row.push_back(std::to_string(option.PricePutCallParity()));
            row.push_back(std::to_string(option.Delta()));
            row.push_back(std::to_string(option.Gamma()));
            row.push_back(std::to_string(option.Vega()));
            row.push_back(std::to_string(option.Theta()));
            row.push_back(std::to_string(option.Rho()));
        }
        else if (m_configuration == "all")
        {
            row.push_back(std::to_string(option.Price()));
            row.push_back(std::to_string(option.PricePutCallParity()));
            row.push_back(std::to_string(option.Delta()));
            row.push_back(std::to_string(option.Gamma()));
            row.push_back(std::to_string(option.Vega()));
            row.push_back(std::to_string(option.Theta()));
            row.push_back(std::to_string(option.Rho()));
            row.push_back(std::to_string(option.Vanna()));
            row.push_back(std::to_string(option.Charm()));
            row.push_back(std::to_string(option.Speed()));
            row.push_back(std::to_string(option.Color()));
            row.push_back(std::to_string(option.DvegaDtime()));
            row.push_back(std::to_string(option.Vomma()));
            row.push_back(std::to_string(option.Veta()));
            row.push_back(std::to_string(option.Zomma()));
            row.push_back(std::to_string(option.Lambda()));
            row.push_back(std::to_string(option.Ultima()));
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
            std::cout << "T: " << row[2] << ", ";
            std::cout << "K: " << row[3] << ", ";
            std::cout << "S: " << row[4] << ", ";
            std::cout << "r: " << row[5] << ", ";
            std::cout << "sigma: " << row[6] << ", ";
            std::cout << "b: " << row[7] << "\n";


            if (m_configuration == "price")
            {
                std::cout << "Price: " << row[8] << "\n";
            }

            else if (m_configuration == "basic")
            {
                std::cout << "Price: " << row[8] << ", ";
                std::cout << "PricePutCallParity: " << row[9] << ", ";
                std::cout << "Delta: " << row[10] << ", ";
                std::cout << "Gamma: " << row[11] << ", ";
                std::cout << "Vega: " << row[12] << ", ";
                std::cout << "Theta: " << row[13] << ", ";
                std::cout << "Rho: " << row[14] << "\n";
            }

            else if (m_configuration == "all")
            {
                std::cout << "Price: " << row[8] << ", ";
                std::cout << "PricePutCallParity: " << row[9] << ", ";
                std::cout << "Delta: " << row[10] << ", ";
                std::cout << "Gamma: " << row[11] << ", ";
                std::cout << "Vega: " << row[12] << ", ";
                std::cout << "Theta: " << row[13] << ", ";
                std::cout << "Rho: " << row[14] << ", ";
                std::cout << "Vanna: " << row[15] << ", ";
                std::cout << "Charm: " << row[16] << ", ";
                std::cout << "Speed: " << row[17] << ", ";
                std::cout << "Color: " << row[18] << ", ";
                std::cout << "DvegaDtime: " << row[19] << ", ";
                std::cout << "Vomma: " << row[20] << ", ";
                std::cout << "Veta: " << row[21] << ", ";
                std::cout << "Zomma: " << row[22] << ", ";
                std::cout << "Lambda: " << row[23] << ", ";
                std::cout << "Ultima: " << row[24] << "\n";
            }
        }
    }

    if (!output_path.empty()) WriteCSV(output_path, output_matrix);

    return output_matrix;
}
