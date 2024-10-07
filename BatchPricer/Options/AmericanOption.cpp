// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// AmericanOption.cpp
// Álvaro Sánchez de Carlos
// Description: this file contains the source code for the AmericanOption class

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "AmericanOption.hpp"

// Function to calculate Y1
double AmericanOption::Y1() const
{
	return 0.5 - m_b / (m_sigma * m_sigma) + std::sqrt(pow(m_b / (m_sigma * m_sigma) - 0.5, 2) + 2 * m_r / (m_sigma * m_sigma));
}

// Function to calculate Y2
double AmericanOption::Y2() const
{
	return 0.5 - m_b / (m_sigma * m_sigma) - std::sqrt(pow(m_b / (m_sigma * m_sigma) - 0.5, 2) + 2 * m_r / (m_sigma * m_sigma));
}

// Constructor for AmericanPerpOption class
AmericanOption::AmericanOption(const std::string& type, const double& K, const double& S, const double& r,
	const double& sigma, const double& b, const int& id) :
	m_type(type),
	m_K(K),
	m_S(S),
	m_r(r),
	m_sigma(sigma),
	m_b(std::isnan(b) ? r : b),
	m_id(id)
{}

// Copy constructor for AmericanPerpOption class
AmericanOption::AmericanOption(const AmericanOption& source) :
	m_type(source.m_type),
	m_K(source.m_K),
	m_S(source.m_S),
	m_r(source.m_r),
	m_sigma(source.m_sigma),
	m_b(source.m_b),
	m_id(source.m_id)
{}

// Assignment operator for AmericanPerpOption class
AmericanOption& AmericanOption::operator=(const AmericanOption& source)
{
	// Check for self assignment
	// Compare the address of the object with 
	// the address of its source object 
	if (this == &source)
		return *this;

	m_type = source.m_type;
	m_K = source.m_K;
	m_S = source.m_S;
	m_r = source.m_r;
	m_sigma = source.m_sigma;
	m_b = source.m_b;
	m_id = source.m_id;

	// Return the current object (the object pointed by this)
	return *this;
}

// Convert option parameters to a vector of strings
std::vector<std::string> AmericanOption::ConvertToVectorString() const
{
	return
	{
		std::to_string(m_id),
		m_type,
		std::to_string(m_K),
		std::to_string(m_S),
		std::to_string(m_r),
		std::to_string(m_sigma),
		std::to_string(m_b)
	};
}

// Calculate the price of the American perpetual option
double AmericanOption::Price() const
{
	if (m_type == "Call")
	{
		double y1 = Y1();
		return m_K / (y1 - 1) * std::pow(((y1 - 1) / y1) * (m_S / m_K), y1);
	}

	if (m_type == "Put")
	{
		double y2 = Y2();
		return m_K / (1 - y2) * std::pow(((y2 - 1) / y2) * (m_S / m_K), y2);
	}
}

// Calculate the AmericanOption Delta of the option
double AmericanOption::NumericDelta(const double& h) const
{
	double up_price = AmericanOption(m_type, m_K, m_S + h, m_r, m_sigma, m_b, m_id).Price();

	double down_price = AmericanOption(m_type, m_K, m_S - h, m_r, m_sigma, m_b, m_id).Price();

	return (up_price - down_price) / (2 * h);
}

// Calculate the numeric Gamma of the option
double AmericanOption::NumericGamma(const double& h) const
{
	double up_price = AmericanOption(m_type, m_K, m_S + h, m_r, m_sigma, m_b, m_id).Price();

	double down_price = AmericanOption(m_type, m_K, m_S - h, m_r, m_sigma, m_b, m_id).Price();

	return (up_price - 2 * Price() + down_price) / (h * h);
}

// Set the option type
AmericanOption& AmericanOption::type(const std::string& type)
{
	m_type = type;
	return *this;
}

// Set the option strike price
AmericanOption& AmericanOption::K(const double& K)
{
	m_K = K;
	return *this;
}

// Set the option spot price
AmericanOption& AmericanOption::S(const double& S)
{
	m_S = S;
	return *this;
}

// Set the risk-free interest rate
AmericanOption& AmericanOption::r(const double& r)
{
	m_r = r;
	return *this;
}

// Set the volatility of the option
AmericanOption& AmericanOption::sigma(const double& sigma)
{
	m_sigma = sigma;
	return *this;
}

// Set the cost of carry
AmericanOption& AmericanOption::b(const double& b)
{
	m_b = b;
	return *this;
}

// Define error function when attempt to set time to expiration
const std::string& AmericanOption::T(const double& T) const
{
	throw std::logic_error("American perpetual options do not have a time to expiration.");
}

// Define << ostream operator function
std::ostream& operator << (std::ostream& os, const AmericanOption& source)
{
	// Sends description to output stream
	os << "Option " << source.m_id << ": " << source.m_type << ", K: " << source.m_K << ", S: "
		<< source.m_S << ", r: " << source.m_r << ", sigma: " << source.m_sigma << ", b: " << source.m_b;

	// Returns the output stream
	return os;
}
