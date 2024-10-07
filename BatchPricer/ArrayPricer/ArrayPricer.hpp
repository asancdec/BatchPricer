// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// ArrayPricer.hpp
// Álvaro Sánchez de Carlos
// Description: this file contains the header code the templated ArrayPricer class

// If ARRAYPRICER_HPP is not defined
#ifndef ARRAYPRICER_HPP
// Define ARRAYPRICER_HPP
#define ARRAYPRICER_HPP

#include <string>
#include <vector>
#include <functional>

#include "../Functions/Functions.hpp"
#include "../Options/EuropeanOption.hpp"
#include "../Options/AmericanOption.hpp"

// Define the ArrayPrice class, derived from a templated OptionType class
template <typename OptionType>
class ArrayPricer : public OptionType
{
private:
    std::vector<double> m_array; // Array of parameter values
    std::string m_parameter; // Parameter to vary
    bool m_print; // Flag to print results
    // Function to write data to a CSV file
    void WriteCSV(const std::string& filename, const std::vector<std::vector<double>>& data) const;

public:
    // Constructor with array of parameter values
    ArrayPricer(const OptionType& option, const std::vector<double>& array,
        const std::string& parameter = "S", const bool& print = true);

    // Constructor with start, end, and step size for parameter values
    ArrayPricer(const OptionType& option, const double& start, const double& end,
        const double& h = 1, const std::string& parameter = "S", const bool& print = true);

    // Copy constructor
    ArrayPricer(const ArrayPricer& source);

    // Assignment operator
    ArrayPricer& operator=(const ArrayPricer& source);

    // Function to price array of options using member function pointer
    std::vector<std::vector<double>> PriceArray(double(OptionType::* func)(void) const, const std::string& output_path = "");
    // Function to price array of options using member function pointer with parameter
    std::vector<std::vector<double>> PriceArray(double(OptionType::* func)(const double&) const, const double& h = 1, const std::string& output_path = "");
};

// Must be the same name as in source file #define
#ifndef ARRAYPRICER_CPP 
#include "ArrayPricer.cpp"
#endif
// It includes the contents of ArrayPricer.cpp in the header file of ARRAYPRICER_CPP is not already defined

// End of the conditional inclusion of the header file
#endif 
