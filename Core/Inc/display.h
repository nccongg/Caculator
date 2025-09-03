/**
  ******************************************************************************
  * @file           : display.h
  * @brief          : Display class header for STM32 Calculator
  * @author         : STM32 Calculator Project
  * @date           : 2024
  ******************************************************************************
  */

#ifndef __DISPLAY_H
#define __DISPLAY_H

#ifdef __cplusplus

#include <string>
#include "stm32f1xx_hal.h"

class Display {
public:
    // Constructor
    Display(UART_HandleTypeDef* huart);
    
    // Destructor
    ~Display();
    
    // Display functions
    void clear();
    void print(const std::string& text);
    void print_line(const std::string& text);
    void print_number(double number);
    void print_error(const std::string& error);
    void print_result(double result);
    void print_operation(char operation);
    
    // Cursor control
    void set_cursor(uint8_t row, uint8_t col);
    void home();
    
    // Special characters
    void print_equals();
    void print_plus();
    void print_minus();
    void print_multiply();
    void print_divide();
    void print_clear();
    
    // Status display
    void show_calculator_mode();
    void show_memory_status(bool has_memory);
    void show_error_status(bool has_error);
    
private:
    // Private member variables
    UART_HandleTypeDef* uart_handle;
    bool lcd_available;
    
    // Private helper methods
    void send_uart_data(const std::string& data);
    void send_uart_data(const char* data);
    void send_uart_byte(uint8_t byte);
    void delay_ms(uint32_t ms);
    
    // LCD specific methods (if available)
    void lcd_init();
    void lcd_send_command(uint8_t command);
    void lcd_send_data(uint8_t data);
    void lcd_write_string(const std::string& text);
};

#endif // __cplusplus

#endif // __DISPLAY_H
