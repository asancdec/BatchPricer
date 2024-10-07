// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// AmericanPerpOption.hpp
// Álvaro Sánchez de Carlos
// Description: this file contains the header code for the AmericanOption class

// Header guard to avoid multiple inclusions
#ifndef AMERICANOPTION_HPP
#define AMERICANOPTION_HPP

#include <string>
#include <vector>
#include "Option.hpp"

// Class definition for American perpetual option
class AmericanOption : public Option
{
private:

	// Option type (Call/Put)
	std::string m_type; 
	// Strike price
	double m_K; 
	// Spot price
	double m_S;
	// Risk-free interest rate
	double m_r; 
	// Volatility
	double m_sigma; 
	// Cost of carry
	double m_b; 
	// Option ID
	int m_id; 

	// Function to calculate Y1
	double Y1() const;
	// Function to calculate Y2
	double Y2() const;

public:

	// Standard functions
	AmericanOption(const std::string& type, const double& K, const double& S, const double& r,
		const double& sigma, const double& b = std::numeric_limits<double>::quiet_NaN(), const int& id = 1);
	AmericanOption(const AmericanOption& source);
	AmericanOption& operator=(const AmericanOption& source);
	std::vector<std::string> ConvertToVectorString() const;

	// Pricing function
	double Price() const;

	// Numeric functions
	double NumericDelta(const double& h) const;
	double NumericGamma(const double& h) const;

	// Parameter modification functions
	AmericanOption& type(const std::string& type);
	AmericanOption& K(const double& K);
	AmericanOption& S(const double& S);
	AmericanOption& r(const double& r);
	AmericanOption& sigma(const double& sigma);
	AmericanOption& b(const double& b);

	// Get inline functions
	const std::string& type() const { return m_type; }
	const double& K() const { return m_K; }
	const double& S() const { return m_S; }
	const double& r() const { return m_r; }
	const double& sigma() const { return m_sigma; }
	const double& b() const { return m_b; }
	const int& id() const { return m_id; }

	// Define error function when attempt to set time
	const std::string& T(const double& T) const;

	// Friend functions
	// Define << ostream operator function
	friend std::ostream& operator << (std::ostream& os, const AmericanOption& source);

};

// AMERICANOPTION_HPP
#endif