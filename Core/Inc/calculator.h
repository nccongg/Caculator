/**
  ******************************************************************************
  * @file           : calculator.h
  * @brief          : Calculator class header for STM32
  * @author         : STM32 Calculator Project
  * @date           : 2024
  ******************************************************************************
  */

#ifndef __CALCULATOR_H
#define __CALCULATOR_H

#ifdef __cplusplus

#include <cstdint>
#include <string>

class Calculator {
public:
    // Constructor
    Calculator();
    
    // Destructor
    ~Calculator();
    
    // Basic arithmetic operations
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    
    // Advanced operations
    double power(double base, double exponent);
    double square_root(double value);
    double percentage(double value, double total);
    
    // Memory functions
    void memory_store(double value);
    double memory_recall();
    void memory_clear();
    void memory_add(double value);
    void memory_subtract(double value);
    
    // Utility functions
    void clear();
    bool is_error() const;
    std::string get_last_error() const;
    double get_last_result() const;
    
    // Input processing
    void process_input(char input);
    void set_operation(char op);
    void calculate_result();
    
private:
    // Private member variables
    double current_value;
    double stored_value;
    double memory_value;
    char current_operation;
    bool has_error;
    std::string error_message;
    double last_result;
    
    // Private helper methods
    void set_error(const std::string& error);
    void clear_error();
    bool validate_operation(double a, double b, char op);
};

#endif // __cplusplus

#endif // __CALCULATOR_H
