/**
  ******************************************************************************
  * @file           : demo.cpp
  * @brief          : Demo program for STM32 Calculator classes
  * @author         : STM32 Calculator Project
  * @date           : 2024
  ******************************************************************************
  */

#include <iostream>
#include <string>
#include "calculator.h"
#include "display.h"
#include "keypad.h"

using namespace std;

// Mock UART handle for testing
UART_HandleTypeDef mock_huart;

int main() {
    std::cout << "=== STM32 Calculator Demo ===" << std::endl;
    
    // Test Calculator class
    std::cout << "\n--- Testing Calculator Class hahahahahahaha---" << std::endl;
    // In ra hình trái tim bằng ký tự ASCII
    std::cout << "  ***     ***  " << std::endl;
    std::cout << " *****   ***** " << std::endl;
    std::cout << "******* *******" << std::endl;
    std::cout << " ************* " << std::endl;
    std::cout << "  ***********  " << std::endl;
    std::cout << "   *********   " << std::endl;
    std::cout << "    *******    " << std::endl;
    std::cout << "     *****     " << std::endl;
    std::cout << "      ***      " << std::endl;
    std::cout << "       *       " << std::endl;
    Calculator calc;
    
    // Test basic operations
    std::cout << "5 + 3 = " << calc.add(5, 3) << std::endl;
    std::cout << "10 - 4 = " << calc.subtract(10, 4) << std::endl;
    std::cout << "6 * 7 = " << calc.multiply(6, 7) << std::endl;
    std::cout << "15 / 3 = " << calc.divide(15, 3) << std::endl;
    
    // Test error handling
    std::cout << "10 / 0 = " << calc.divide(10, 0) << std::endl;
    if (calc.is_error()) {
        std::cout << "Error: " << calc.get_last_error() << std::endl;
    }
    
    // Test advanced operations
    std::cout << "2^8 = " << calc.power(2, 8) << std::endl;
    std::cout << "sqrt(144) = " << calc.square_root(144) << std::endl;
    std::cout << "25% of 200 = " << calc.percentage(25, 200) << std::endl;
    
    // Test memory functions
    calc.memory_store(100);
    std::cout << "Memory stored: 100" << std::endl;
    std::cout << "Memory recall: " << calc.memory_recall() << std::endl;
    
    calc.memory_add(50);
    std::cout << "Memory + 50 = " << calc.memory_recall() << std::endl;
    
    // Test Display class
    std::cout << "\n--- Testing Display Class ---" << std::endl;
    Display display(&mock_huart);
    
    display.show_calculator_mode();
    display.print_line("Hello World!");
    display.print_number(3.14159);
    display.print_operation('+');
    display.print_result(42.0);
    
    // Test Keypad class
    std::cout << "\n--- Testing Keypad Class ---" << std::endl;
    Keypad keypad;
    
    // Test key validation
    std::cout << "Is '5' valid? " << (keypad.is_valid_key('5') ? "Yes" : "No") << std::endl;
    std::cout << "Is '+' valid? " << (keypad.is_valid_key('+') ? "Yes" : "No") << std::endl;
    std::cout << "Is 'X' valid? " << (keypad.is_valid_key('X') ? "Yes" : "No") << std::endl;
    
    // Test input processing
    std::cout << "\n--- Testing Input Processing ---" << std::endl;
    calc.clear();
    
    // Simulate keypad input: 123 + 456 =
    calc.process_input('1');
    calc.process_input('2');
    calc.process_input('3');
    calc.process_input('+');
    calc.process_input('4');
    calc.process_input('5');
    calc.process_input('6');
    calc.process_input('=');
    
    std::cout << "Result: " << calc.get_last_result() << std::endl;
    
    // Test complex calculation
    std::cout << "\n--- Testing Complex Calculation ---" << std::endl;
    calc.clear();
    
    // Calculate: (10 + 5) * 2
    calc.process_input('1');
    calc.process_input('0');
    calc.process_input('+');
    calc.process_input('5');
    calc.process_input('=');
    
    double temp_result = calc.get_last_result();
    std::cout << "10 + 5 = " << temp_result << std::endl;
    
    calc.process_input('*');
    calc.process_input('2');
    calc.process_input('=');
    
    std::cout << "(" << temp_result << ") * 2 = " << calc.get_last_result() << std::endl;
    
    std::cout << "\n=== Demo Complete ===" << std::endl;
    return 0;
}
