// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// Functions.cpp
// Álvaro Sánchez de Carlos
// Description: this file contains the source code of global functions

#include <iostream>
#include <vector>
#include "Functions.hpp"

// Function to create an array of doubles from start to end with step size h
std::vector<double> createArray(const double& start, const double& end, const double& h)
{
    std::vector<double> array;
    for (double parameter = start; parameter <= end; parameter += h)
    {
        array.push_back(parameter);
    }
    return array;
}
