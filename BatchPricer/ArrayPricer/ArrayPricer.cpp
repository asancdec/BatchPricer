// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// ArrayPricer.cpp
// Álvaro Sánchez de Carlos
// Description: this file contains the source code the templated ArrayPricer class

// If ARRAYPRICER_CPP is not defined
#ifndef ARRAYPRICER_CPP
// Define ARRAYPRICER_CPP
#define ARRAYPRICER_CPP

#include <string>
#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "ArrayPricer.hpp"

// Function to write data to a CSV file
template <typename OptionType>
void ArrayPricer<OptionType>::WriteCSV(const std::string& filename, const std::vector<std::vector<double>>& output_matrix) const
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Could not open the file for writing!" << std::endl;
        return;
    }

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

// Constructor with array of parameter values
template <typename OptionType>
ArrayPricer<OptionType>::ArrayPricer(const OptionType& option, const std::vector<double>& array,
    const std::string& parameter, const bool& print) :
    OptionType(option),
    m_array(array),
    m_parameter(parameter),
    m_print(print)
{}

// Constructor with start, end, and step size for parameter values
template <typename OptionType>
ArrayPricer<OptionType>::ArrayPricer(const OptionType& option, const double& start, const double& end,
    const double& h, const std::string& parameter, const bool& print) :
    OptionType(option),
    m_array(createArray(start, end, h)),
    m_parameter(parameter),
    m_print(print)
{}

// Copy constructor
template <typename OptionType>
ArrayPricer<OptionType>::ArrayPricer(const ArrayPricer& source) :
    OptionType(source),
    m_array(source.m_array),
    m_parameter(source.m_parameter),
    m_print(source.m_print)
{}

// Assignment operator
template <typename OptionType>
ArrayPricer<OptionType>& ArrayPricer<OptionType>::operator=(const ArrayPricer& source)
{
    // Check for self assignment
    if (this == &source)
        return *this;

    OptionType::operator=(source);
    m_array = source.m_array;
    m_parameter = source.m_parameter;
    m_print = source.m_print;

    return *this;
}

// Function to price array of options using member function pointer
template <typename OptionType>
std::vector<std::vector<double>> ArrayPricer<OptionType>::PriceArray(double(OptionType::* func)(void) const, const std::string& output_path)
{
    std::vector<std::vector<double>> output_matrix;
    std::vector<double> price_array;

    if (m_parameter == "T")
    {
        for (const auto& parameter : m_array)
        {
            this->T(parameter);
            price_array.push_back((this->*func)());
        }
    }

    else if (m_parameter == "K")
    {
        for (const auto& parameter : m_array)
        {
            this->K(parameter);
            price_array.push_back((this->*func)());
        }
    }
    else if (m_parameter == "S")
    {
        for (const auto& parameter : m_array)
        {
            this->S(parameter);
            price_array.push_back((this->*func)());
        }
    }
    else if (m_parameter == "r")
    {
        for (const auto& parameter : m_array)
        {
            this->r(parameter);
            price_array.push_back((this->*func)());
        }
    }
    else if (m_parameter == "sigma")
    {
        for (const auto& parameter : m_array)
        {
            this->sigma(parameter);
            price_array.push_back((this->*func)());
        }
    }
    else if (m_parameter == "b")
    {
        for (const auto& parameter : m_array)
        {
            this->b(parameter);
            price_array.push_back((this->*func)());
        }
    }

    if (m_print)
    {
        std::cout << *this << std::endl;

        for (int i = 0; i < m_array.size(); ++i)
        {
            std::cout << m_parameter << ": " << m_array[i] << " -> " << price_array[i] << std::endl;
        }
    }

    output_matrix.push_back(m_array);
    output_matrix.push_back(price_array);

    if (!output_path.empty()) WriteCSV(output_path, output_matrix);

    return output_matrix;
}

// Function to price array of options using member function pointer with parameter
template <typename OptionType>
std::vector<std::vector<double>> ArrayPricer<OptionType>::PriceArray(double(OptionType::* func)(const double&) const, const double& h, const std::string& output_path)
{
    std::vector<std::vector<double>> output_matrix;
    std::vector<double> price_array;

    if (m_parameter == "T")
    {
        for (const auto& parameter : m_array)
        {
            this->T(parameter);
            price_array.push_back((this->*func)(h));
        }
    }
    else if (m_parameter == "K")
    {
        for (const auto& parameter : m_array)
        {
            this->K(parameter);
            price_array.push_back((this->*func)(h));
        }
    }
    else if (m_parameter == "S")
    {
        for (const auto& parameter : m_array)
        {
            this->S(parameter);
            price_array.push_back((this->*func)(h));
        }
    }
    else if (m_parameter == "r")
    {
        for (const auto& parameter : m_array)
        {
            this->r(parameter);
            price_array.push_back((this->*func)(h));
        }
    }
    else if (m_parameter == "sigma")
    {
        for (const auto& parameter : m_array)
        {
            this->sigma(parameter);
            price_array.push_back((this->*func)(h));
        }
    }
    else if (m_parameter == "b")
    {
        for (const auto& parameter : m_array)
        {
            this->b(parameter);
            price_array.push_back((this->*func)(h));
        }
    }

    if (m_print)
    {
        std::cout << *this << std::endl;

        for (int i = 0; i < m_array.size(); ++i)
        {
            std::cout << m_parameter << ": " << m_array[i] << " -> " << price_array[i] << std::endl;
        }
    }

    output_matrix.push_back(m_array);
    output_matrix.push_back(price_array);

    if (!output_path.empty()) WriteCSV(output_path, output_matrix);

    return output_matrix;
}

// End of the conditional inclusion of the header file
#endif
