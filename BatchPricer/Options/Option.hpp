// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// Option.hpp
// Álvaro Sánchez de Carlos
// Description: this file contains the source code the of the Option base abtract class

// Conditional header guard to avoid multiple inclusions
#ifndef OPTION_HPP
#define OPTION_HPP

// Abstract class representing an option
class Option
{
public:
    // Pure virtual function to ensure derived classes implement the Price function
    virtual double Price() const = 0;
};

// OPTION_HPP
#endif 
