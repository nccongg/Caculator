/**
  ******************************************************************************
  * @file           : display.cpp
  * @brief          : Display class implementation for STM32 Calculator
  * @author         : STM32 Calculator Project
  * @date           : 2024
  ******************************************************************************
  */

#include "display.h"
#include <cstring>
#include <sstream>
#include <iomanip>

// Constructor
Display::Display(UART_HandleTypeDef* huart) 
    : uart_handle(huart)
    , lcd_available(false) {
    
    if (uart_handle != nullptr) {
        // UART is available
    }
}

// Destructor
Display::~Display() {
}

// Display functions
void Display::clear() {
    if (lcd_available) {
        lcd_send_command(0x01);  // Clear display
        lcd_send_command(0x02);  // Return home
    } else {
        send_uart_data("\033[2J\033[H");  // Clear screen and home cursor
    }
}

void Display::print(const std::string& text) {
    if (lcd_available) {
        lcd_write_string(text);
    } else {
        send_uart_data(text);
    }
}

void Display::print_line(const std::string& text) {
    print(text);
    if (lcd_available) {
        lcd_send_command(0xC0);  // Move to second line
    } else {
        send_uart_data("\r\n");
    }
}

void Display::print_number(double number) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << number;
    
    // Remove trailing zeros
    std::string str = oss.str();
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') str.pop_back();
    
    print(str);
}

void Display::print_error(const std::string& error) {
    if (lcd_available) {
        clear();
        lcd_write_string("ERROR:");
        lcd_send_command(0xC0);
        lcd_write_string(error);
    } else {
        send_uart_data("ERROR: ");
        send_uart_data(error);
        send_uart_data("\r\n");
    }
}

void Display::print_result(double result) {
    if (lcd_available) {
        lcd_send_command(0xC0);  // Move to second line
        lcd_write_string("= ");
        print_number(result);
    } else {
        send_uart_data(" = ");
        print_number(result);
        send_uart_data("\r\n");
    }
}

void Display::print_operation(char operation) {
    std::string op_str;
    switch (operation) {
        case '+': op_str = " + "; break;
        case '-': op_str = " - "; break;
        case '*': op_str = " * "; break;
        case '/': op_str = " / "; break;
        case '=': op_str = " = "; break;
        default: op_str = " "; break;
    }
    print(op_str);
}

// Cursor control
void Display::set_cursor(uint8_t row, uint8_t col) {
    if (lcd_available) {
        uint8_t address = (row == 0) ? 0x80 : 0xC0;
        address += col;
        lcd_send_command(address);
    } else {
        // For UART, we can't control cursor position easily
        // Just print newlines to simulate
        for (uint8_t i = 0; i < row; i++) {
            send_uart_data("\r\n");
        }
    }
}

void Display::home() {
    if (lcd_available) {
        lcd_send_command(0x02);
    } else {
        send_uart_data("\033[H");
    }
}

// Special characters
void Display::print_equals() {
    print(" = ");
}

void Display::print_plus() {
    print(" + ");
}

void Display::print_minus() {
    print(" - ");
}

void Display::print_multiply() {
    print(" * ");
}

void Display::print_divide() {
    print(" / ");
}

void Display::print_clear() {
    print("CLEAR");
}

// Status display
void Display::show_calculator_mode() {
    if (lcd_available) {
        lcd_send_command(0x80);
        lcd_write_string("CALCULATOR");
    } else {
        send_uart_data("=== STM32 CALCULATOR ===\r\n");
    }
}

void Display::show_memory_status(bool has_memory) {
    if (lcd_available) {
        lcd_send_command(0x8F);  // Top right corner
        lcd_write_string(has_memory ? "M" : " ");
    } else {
        send_uart_data(has_memory ? "[M] " : "    ");
    }
}

void Display::show_error_status(bool has_error) {
    if (lcd_available) {
        lcd_send_command(0x8E);  // Top right corner - 1
        lcd_write_string(has_error ? "E" : " ");
    } else {
        send_uart_data(has_error ? "[E] " : "    ");
    }
}

// Private helper methods
void Display::send_uart_data(const std::string& data) {
    if (uart_handle != nullptr) {
        HAL_UART_Transmit(uart_handle, (uint8_t*)data.c_str(), data.length(), 1000);
    }
}

void Display::send_uart_data(const char* data) {
    if (uart_handle != nullptr) {
        HAL_UART_Transmit(uart_handle, (uint8_t*)data, strlen(data), 1000);
    }
}

void Display::send_uart_byte(uint8_t byte) {
    if (uart_handle != nullptr) {
        HAL_UART_Transmit(uart_handle, &byte, 1, 1000);
    }
}

void Display::delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}

// LCD specific methods (if available)
void Display::lcd_init() {
    // Initialize LCD in 4-bit mode
    delay_ms(50);
    
    lcd_send_command(0x33);
    delay_ms(5);
    lcd_send_command(0x32);
    delay_ms(5);
    lcd_send_command(0x28);  // 4-bit mode, 2 lines, 5x8 font
    delay_ms(5);
    lcd_send_command(0x0C);  // Display on, cursor off, blink off
    delay_ms(5);
    lcd_send_command(0x06);  // Increment cursor, no display shift
    delay_ms(5);
    lcd_send_command(0x01);  // Clear display
    delay_ms(5);
    
    lcd_available = true;
}

void Display::lcd_send_command(uint8_t command) {
    // This would need to be implemented based on your LCD hardware
    // For now, just a placeholder
}

void Display::lcd_send_data(uint8_t data) {
    // This would need to be implemented based on your LCD hardware
    // For now, just a placeholder
}

void Display::lcd_write_string(const std::string& text) {
    for (char c : text) {
        lcd_send_data(c);
    }
}
