// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// MatrixPricerAmerican.hpp
// Álvaro Sánchez de Carlos
// Description: this file contains the header code the MatrixPricerAmerican class

// If MATRIXPRICERAMERICAN_HPP is not defined
#ifndef MATRIXPRICERAMERICAN_HPP
// Define MATRIXPRICERAMERICAN_HPP
#define MATRIXPRICERAMERICAN_HPP

#include <vector>
#include <string>
#include "../Options/AmericanOption.hpp"

// Class definition for MatrixPricerAmerican
class MatrixPricerAmerican
{
private:

    // Matrix of American perpetual options
    std::vector<AmericanOption> m_matrix;
    // Configuration setting
    std::string m_configuration;
    // Flag to print results
    bool m_print; 

    // Function to write data to a CSV file
    void WriteCSV(const std::string& output_path, const std::vector<std::vector<std::string>>& output_matrix) const;

public:

    // Constructor with matrix of options
    MatrixPricerAmerican(const std::vector<AmericanOption>& matrix, const bool& print = true, const std::string& configuration = "all");

    // Constructor with input file path
    MatrixPricerAmerican(const std::string& input_path, const bool& print = true, const std::string& configuration = "all");

    // Copy constructor
    MatrixPricerAmerican(const MatrixPricerAmerican& source);

    // Assignment operator
    MatrixPricerAmerican& operator=(const MatrixPricerAmerican& source);

    // Function to price the matrix of options
    std::vector<std::vector<std::string>> Price(const double& h = 1, const std::string& output_path = "") const;
};

// End of the conditional inclusion of the header file
#endif
