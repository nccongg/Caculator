/**
  ******************************************************************************
  * @file           : keypad.h
  * @brief          : Keypad class header for STM32 Calculator
  * @author         : STM32 Calculator Project
  * @date           : 2024
  ******************************************************************************
  */

#ifndef __KEYPAD_H
#define __KEYPAD_H

#ifdef __cplusplus

#include <cstdint>
#include <functional>
#include "stm32f1xx_hal.h"

// Key definitions
#define KEY_0           '0'
#define KEY_1           '1'
#define KEY_2           '2'
#define KEY_3           '3'
#define KEY_4           '4'
#define KEY_5           '5'
#define KEY_6           '6'
#define KEY_7           '7'
#define KEY_8           '8'
#define KEY_9           '9'
#define KEY_PLUS        '+'
#define KEY_MINUS       '-'
#define KEY_MULTIPLY    '*'
#define KEY_DIVIDE      '/'
#define KEY_EQUALS      '='
#define KEY_CLEAR       'C'
#define KEY_DECIMAL     '.'
#define KEY_MEMORY      'M'
#define KEY_MEMORY_ADD  'M+'
#define KEY_MEMORY_SUB  'M-'
#define KEY_MEMORY_RECALL 'MR'
#define KEY_MEMORY_CLEAR 'MC'

class Keypad {
public:
    // Constructor
    Keypad();
    
    // Destructor
    ~Keypad();
    
    // Keypad initialization
    void init();
    void init_gpio();
    void init_timer();
    
    // Key scanning
    char scan_key();
    bool is_key_pressed();
    char get_pressed_key();
    
    // Debouncing
    void debounce_delay();
    bool is_valid_key(char key);
    
    // Event handling
    void set_key_callback(std::function<void(char)> callback);
    void handle_key_event();
    
    // Status checking
    bool is_initialized() const;
    uint32_t get_last_key_time() const;
    
    // GPIO control
    void set_row_pins(GPIO_TypeDef* port, uint16_t* pins);
    void set_col_pins(GPIO_TypeDef* port, uint16_t* pins);
    
private:
    // Private member variables
    GPIO_TypeDef* row_port;
    GPIO_TypeDef* col_port;
    uint16_t row_pins[4];
    uint16_t col_pins[4];
    
    bool initialized;
    uint32_t last_key_time;
    char last_key;
    std::function<void(char)> key_callback;
    
    // Private helper methods
    void scan_matrix();
    char decode_key(uint8_t row, uint8_t col);
    bool read_row(uint8_t row);
    bool read_column(uint8_t col);
    void set_row_high(uint8_t row);
    void set_row_low(uint8_t row);
    void set_col_high(uint8_t col);
    void set_col_low(uint8_t col);
    
    // Timer handling
    void start_timer();
    void stop_timer();
    void timer_callback();
};

#endif // __cplusplus

#endif // __KEYPAD_H
