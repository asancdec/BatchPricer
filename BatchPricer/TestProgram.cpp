// C++: Batch Option Pricer with Analytical and Numerical Sensitivities
// PlainOptions.cpp
// Álvaro Sánchez de Carlos
// Description: this file contains the main function with a sample code to test the program


#include <iostream>

#include "Functions/Functions.hpp"
#include "Options/EuropeanOption.hpp"
#include "Options/AmericanOption.hpp"
#include "ArrayPricer/ArrayPricer.hpp"
#include "MatrixPricer/MatrixPricerEuropean.hpp"
#include "MatrixPricer/MatrixPricerAmerican.hpp"

// Main function of the program
int main()
{

    // Price European Call and Put options using the Black-Scholes Model (BSM)
    EuropeanOption option_1("Call", 0.25, 65, 60, 0.08, 0.3, 1);
    std::cout << option_1 << ", Price: " << option_1.Price() << std::endl;
    option_1.type("Put");
    std::cout << option_1 << ", Price: " << option_1.Price() << std::endl;

    EuropeanOption option_2("Call", 1.0, 100, 100, 0.00, 0.2, 2);
    std::cout << option_2 << ", Price: " << option_2.Price() << std::endl;
    option_2.type("Put");
    std::cout << option_2 << ", Price: " << option_2.Price() << std::endl;

    EuropeanOption option_3("Call", 1.0, 10, 5, 0.12, 0.5, 3);
    std::cout << option_3 << ", Price: " << option_3.Price() << std::endl;
    option_3.type("Put");
    std::cout << option_3 << ", Price: " << option_3.Price() << std::endl;

    EuropeanOption option_4("Call", 30, 100, 100, 0.08, 0.3, 4);
    std::cout << option_4 << ", Price: " << option_4.Price() << std::endl;
    option_4.type("Put");
    std::cout << option_4 << ", Price: " << option_4.Price() << std::endl;

    // Apply Put-Call parity to calculate the price of the associated Call option
    std::cout << option_1 << " Call Price: " << option_1.PricePutCallParity() << std::endl;
    std::cout << option_2 << " Call Price: " << option_2.PricePutCallParity() << std::endl;
    std::cout << option_3 << " Call Price: " << option_3.PricePutCallParity() << std::endl;
    std::cout << option_4 << " Call Price: " << option_4.PricePutCallParity() << std::endl;

    // Check for arbitrage opportunities using the Put-Call parity relationship
    option_1.CheckPutCallParity(2.1534, 0.05);
    option_1.CheckPutCallParity(2.5534, 0.05);

    // Price a range of European Options using ArrayPricer class and save the output to CSV
    ArrayPricer<EuropeanOption>(option_1, 10, 200, 5, "S", true).PriceArray(&EuropeanOption::Price, "Outputs/ArrayPricer.csv");

    // Price a batch of European Options from a CSV file using MatrixPricerEuropean class and save the results
    MatrixPricerEuropean("Inputs/EuropeanOptionBatch.csv", true, "price").Price("Outputs/EuropeanOptionBatchPriced.csv");

    // Calculate the Delta and Gamma for a European Option on a future
    EuropeanOption option_5("Call", 0.5, 100, 105, 0.1, 0.36, 5, 0);
    std::cout << option_5 << ", Delta: " << option_5.Delta() << ", Gamma: " << option_5.Gamma() << std::endl;
    option_5.type("Put");
    std::cout << option_5 << ", Delta: " << option_5.Delta() << ", Gamma: " << option_5.Gamma() << std::endl;

    // Calculate option sensitivity (Delta) for an array of European Options
    ArrayPricer<EuropeanOption>(option_5.type("Call"), 10, 200, 5, "S", true).PriceArray(&EuropeanOption::Delta);

    // Apply sensitivity formulas (e.g., Delta, Gamma) to a batch of European Options using MatrixPricerEuropean
    MatrixPricerEuropean("Inputs/EuropeanOptionBatch.csv", true, "all").Price("Outputs/EuropeanOptionBatchAll.csv");

    // Calculate the numerical Delta for different shock sizes using ArrayPricer
    std::cout << "Numeric Delta with a shock size of 20" << std::endl;
    ArrayPricer<EuropeanOption>(option_5, 20, 200, 20, "S", true).PriceArray(&EuropeanOption::NumericDelta, 20);
    std::cout << "Numeric Delta with a shock size of 5" << std::endl;
    ArrayPricer<EuropeanOption>(option_5, 20, 200, 20, "S", true).PriceArray(&EuropeanOption::NumericDelta, 5);
    std::cout << "Numeric Delta with a shock size of 0.001" << std::endl;
    ArrayPricer<EuropeanOption>(option_5, 20, 200, 20, "S", true).PriceArray(&EuropeanOption::NumericDelta, 0.001);
    std::cout << "Delta using its analytical formula" << std::endl;
    ArrayPricer<EuropeanOption>(option_5, 20, 200, 20, "S", true).PriceArray(&EuropeanOption::NumericDelta, 0.001);

    // Test American Perpetual Option pricing for both Call and Put options
    AmericanOption option_6("Call", 100, 110, 0.1, 0.1, 0.02, 6);
    std::cout << option_6 << ", Price: " << option_6.Price() << std::endl;
    option_6.type("Put");
    std::cout << option_6 << ", Price: " << option_6.Price() << std::endl;

    // Price an array of American Perpetual Options using ArrayPricer class
    ArrayPricer<AmericanOption>(option_6, 10, 200, 10, "S", true).PriceArray(&AmericanOption::Price);

    // Handle exception for invalid inputs (e.g., American Perpetual Options do not have time to expiration)
    try
    {
        ArrayPricer<AmericanOption>(option_6, 10, 200, 10, "T", true).PriceArray(&AmericanOption::Price);
    }
    catch (const std::logic_error& e)
    {
        std::cerr << "Error: " << e.what() << "\n" << std::endl;
    }

    // Price a matrix of American Perpetual Options using the MatrixPricerAmerican class and save the results
    MatrixPricerAmerican("Inputs/AmericanOptionBatch.csv", true, "all").Price(0.5, "Outputs/AmericanOptionBatchPriced.csv");

    // Return 0 to indicate successful execution
    return 0;
}
