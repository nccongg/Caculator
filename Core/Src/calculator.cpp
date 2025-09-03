/**
  ******************************************************************************
  * @file           : calculator.cpp
  * @brief          : Calculator class implementation for STM32
  * @author         : STM32 Calculator Project
  * @date           : 2024
  ******************************************************************************
  */

#include "calculator.h"
#include <cmath>
#include <cstring>

// Constructor
Calculator::Calculator() 
    : current_value(0.0)
    , stored_value(0.0)
    , memory_value(0.0)
    , current_operation('\0')
    , has_error(false)
    , error_message("")
    , last_result(0.0) {
}

// Destructor
Calculator::~Calculator() {
}

// Basic arithmetic operations
double Calculator::add(double a, double b) {
    if (validate_operation(a, b, '+')) {
        last_result = a + b;
        return last_result;
    }
    return 0.0;
}

double Calculator::subtract(double a, double b) {
    if (validate_operation(a, b, '-')) {
        last_result = a - b;
        return last_result;
    }
    return 0.0;
}

double Calculator::multiply(double a, double b) {
    if (validate_operation(a, b, '*')) {
        last_result = a * b;
        return last_result;
    }
    return 0.0;
}

double Calculator::divide(double a, double b) {
    if (b == 0.0) {
        set_error("Division by zero");
        return 0.0;
    }
    
    if (validate_operation(a, b, '/')) {
        last_result = a / b;
        return last_result;
    }
    return 0.0;
}

// Advanced operations
double Calculator::power(double base, double exponent) {
    if (validate_operation(base, exponent, '^')) {
        last_result = pow(base, exponent);
        return last_result;
    }
    return 0.0;
}

double Calculator::square_root(double value) {
    if (value < 0.0) {
        set_error("Invalid input for square root");
        return 0.0;
    }
    
    last_result = sqrt(value);
    return last_result;
}

double Calculator::percentage(double value, double total) {
    if (total == 0.0) {
        set_error("Invalid percentage calculation");
        return 0.0;
    }
    
    last_result = (value / total) * 100.0;
    return last_result;
}

// Memory functions
void Calculator::memory_store(double value) {
    memory_value = value;
    clear_error();
}

double Calculator::memory_recall() {
    return memory_value;
}

void Calculator::memory_clear() {
    memory_value = 0.0;
}

void Calculator::memory_add(double value) {
    memory_value += value;
}

void Calculator::memory_subtract(double value) {
    memory_value -= value;
}

// Utility functions
void Calculator::clear() {
    current_value = 0.0;
    stored_value = 0.0;
    current_operation = '\0';
    clear_error();
}

bool Calculator::is_error() const {
    return has_error;
}

std::string Calculator::get_last_error() const {
    return error_message;
}

double Calculator::get_last_result() const {
    return last_result;
}

// Input processing
void Calculator::process_input(char input) {
    if (has_error) {
        clear_error();
    }
    
    switch (input) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            current_value = current_value * 10.0 + (input - '0');
            break;
            
        case '.':
            // Handle decimal point
            break;
            
        case '+': case '-': case '*': case '/':
            set_operation(input);
            break;
            
        case '=':
            calculate_result();
            break;
            
        case 'C':
            clear();
            break;
            
        case 'M':
            // Memory operations
            break;
            
        default:
            break;
    }
}

void Calculator::set_operation(char op) {
    if (current_operation != '\0') {
        calculate_result();
    }
    
    stored_value = current_value;
    current_operation = op;
    current_value = 0.0;
}

void Calculator::calculate_result() {
    if (current_operation == '\0') {
        return;
    }
    
    switch (current_operation) {
        case '+':
            current_value = add(stored_value, current_value);
            break;
        case '-':
            current_value = subtract(stored_value, current_value);
            break;
        case '*':
            current_value = multiply(stored_value, current_value);
            break;
        case '/':
            current_value = divide(stored_value, current_value);
            break;
        default:
            break;
    }
    
    current_operation = '\0';
    stored_value = 0.0;
}

// Private helper methods
void Calculator::set_error(const std::string& error) {
    has_error = true;
    error_message = error;
}

void Calculator::clear_error() {
    has_error = false;
    error_message = "";
}

bool Calculator::validate_operation(double a, double b, char op) {
    // Basic validation - can be extended
    if (std::isnan(a) || std::isnan(b) || std::isinf(a) || std::isinf(b)) {
        set_error("Invalid number");
        return false;
    }
    
    clear_error();
    return true;
}
