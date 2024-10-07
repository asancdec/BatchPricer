// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// Functions.hpp
// Álvaro Sánchez de Carlos
// Description: this file contains the header code of global functions

// If FUNCTIONS_HPP is not defined
#ifndef FUNCTIONS_HPP
// Define FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>

// Function to create an array of doubles from start to end with step size h
std::vector<double> createArray(const double& start, const double& end, const double& h = 2);

// End of the conditional inclusion of the header file
#endif
