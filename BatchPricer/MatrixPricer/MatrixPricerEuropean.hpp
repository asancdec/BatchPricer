// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// MatrixPricerEuropean.hpp
// Álvaro Sánchez de Carlos
// Description: this file contains the header code the MatrixPricerEuropean class

// If MATRIXPRICEREUROPEAN_HPP is not defined
#ifndef MATRIXPRICEREUROPEAN_HPP
// Define MATRIXPRICEREUROPEAN_HPP
#define MATRIXPRICEREUROPEAN_HPP

#include <vector>
#include <string>
#include "../Options/EuropeanOption.hpp"

// Class definition for MatrixPricerEuropean
class MatrixPricerEuropean
{
private:

    // Matrix of European options
    std::vector<EuropeanOption> m_matrix;
    // Configuration setting
    std::string m_configuration; 
    // Flag to print results
    bool m_print;

    // Function to write data to a CSV file
    void WriteCSV(const std::string& output_path, const std::vector<std::vector<std::string>>& output_matrix) const;

public:

    // Constructor with matrix of options
    MatrixPricerEuropean(const std::vector<EuropeanOption>& matrix, const bool& print = true, const std::string& configuration = "all");

    // Constructor with input file path
    MatrixPricerEuropean(const std::string& input_path, const bool& print = true, const std::string& configuration = "all");

    // Copy constructor
    MatrixPricerEuropean(const MatrixPricerEuropean& source);

    // Assignment operator
    MatrixPricerEuropean& operator=(const MatrixPricerEuropean& source);

    // Function to price the matrix of options
    std::vector<std::vector<std::string>> Price(const std::string& output_path = "") const;
};

// End of the conditional inclusion of the header file
#endif
