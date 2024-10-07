# (C++) Batch Option Pricer with Analytical and Numerical Sensitivities

## Overview
The **Batch Option Pricer** is a comprehensive C++ tool designed to perform batch pricing and sensitivity analysis for financial options. It supports both European and American options, employing the Black-Scholes Model (BSM) for analytical pricing of European options. Additionally, the tool provides functionalities for calculating numerical sensitivities, such as Delta, allowing users to assess how option prices respond to underlying asset fluctuations.

Beyond pricing, the Batch Option Pricer offers robust tools for arbitrage detection via the Put-Call parity relationship, ensuring that users can identify discrepancies in option pricing that may indicate potential arbitrage opportunities. For flexibility, the program can process batches of options from CSV files, making it suitable for large-scale, automated pricing tasks. The **ArrayPricer** and **MatrixPricer** classes further enhance this functionality by enabling pricing of multiple options in a streamlined, efficient manner.

## Features
- **European and American Option Pricing**: Uses the Black-Scholes Model (BSM) for European options.
- **Put-Call Parity Analysis**: Evaluates associated option prices and identifies arbitrage opportunities.
- **Sensitivity Analysis**: Calculates a comprehensive range of sensitivities for options, including:
  - **First-Order Sensitivities**: Delta, Gamma, Vega, Theta, and Rho.
  - **Second-Order Sensitivities**: Vanna, Charm, Speed, Color, DvegaDtime, Vomma, Veta, Zomma, Lambda, and Ultima.
- **Batch Processing**: Prices multiple options using data from CSV files.
- **Numerical Sensitivities**: Calculates numerical values of Delta and Gamma with customizable shock sizes.
- **Array and Matrix Processing**:
  - *ArrayPricer*: Prices a series of European options.
  - *MatrixPricer*: Supports batch processing of both European and American options from CSV files.

## File Structure

- **BatchPricer**
  - **ArrayPricer**
    - `ArrayPricer.cpp`
    - `ArrayPricer.hpp`
  - **Functions**
    - `Functions.cpp`
  - **Inputs**
    - `MatrixAmerican.csv`
    - `MatrixEuropean.csv`
  - **Outputs**
  - **Options**
    - `AmericanOption.cpp`
    - `AmericanOption.hpp`
    - `EuropeanOption.cpp`
    - `EuropeanOption.hpp`
- **TestProgram.cpp**

## Usage
To compile the BatchPricer project, use a C++ compiler. Example command:

```bash
g++ -o BatchPricer TestProgram.cpp Functions/Functions.cpp Options/*.cpp ArrayPricer/ArrayPricer.cpp MatrixPricer/*.cpp
