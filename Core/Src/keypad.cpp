/**
  ******************************************************************************
  * @file           : keypad.cpp
  * @brief          : Keypad class implementation for STM32 Calculator
  * @author         : STM32 Calculator Project
  * @date           : 2024
  ******************************************************************************
  */

#include "keypad.h"
#include <cstring>

// Constructor
Keypad::Keypad() 
    : row_port(nullptr)
    , col_port(nullptr)
    , initialized(false)
    , last_key_time(0)
    , last_key('\0')
    , key_callback(nullptr) {
    
    // Initialize pin arrays
    memset(row_pins, 0, sizeof(row_pins));
    memset(col_pins, 0, sizeof(col_pins));
}

// Destructor
Keypad::~Keypad() {
}

// Keypad initialization
void Keypad::init() {
    init_gpio();
    init_timer();
    initialized = true;
}

void Keypad::init_gpio() {
    // This would need to be implemented based on your specific GPIO configuration
    // For now, just a placeholder
    
    // Example for STM32F103C8T6:
    // Row pins: PA0, PA1, PA2, PA3
    // Col pins: PA4, PA5, PA6, PA7
    
    // Enable GPIO clocks
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // Configure row pins as output
    GPIO_InitTypeDef gpio_init = {0};
    gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio_init);
    
    // Configure col pins as input with pull-up
    gpio_init.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    gpio_init.Mode = GPIO_MODE_INPUT;
    gpio_init.Pull = GPIO_PULLUP;
    gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio_init);
    
    // Set default pin configuration
    row_port = GPIOA;
    col_port = GPIOA;
    row_pins[0] = GPIO_PIN_0;
    row_pins[1] = GPIO_PIN_1;
    row_pins[2] = GPIO_PIN_2;
    row_pins[3] = GPIO_PIN_3;
    col_pins[0] = GPIO_PIN_4;
    col_pins[1] = GPIO_PIN_5;
    col_pins[2] = GPIO_PIN_6;
    col_pins[3] = GPIO_PIN_7;
}

void Keypad::init_timer() {
    // This would need to be implemented based on your timer configuration
    // For now, just a placeholder
}

// Key scanning
char Keypad::scan_key() {
    if (!initialized) {
        return '\0';
    }
    
    for (uint8_t row = 0; row < 4; row++) {
        set_row_high(row);
        
        for (uint8_t col = 0; col < 4; col++) {
            if (read_column(col)) {
                char key = decode_key(row, col);
                set_row_low(row);
                return key;
            }
        }
        
        set_row_low(row);
    }
    
    return '\0';
}

bool Keypad::is_key_pressed() {
    return scan_key() != '\0';
}

char Keypad::get_pressed_key() {
    char key = scan_key();
    if (key != '\0') {
        last_key = key;
        last_key_time = HAL_GetTick();
    }
    return key;
}

// Debouncing
void Keypad::debounce_delay() {
    HAL_Delay(50);  // 50ms debounce delay
}

bool Keypad::is_valid_key(char key) {
    return (key >= '0' && key <= '9') || 
           key == '+' || key == '-' || key == '*' || key == '/' ||
           key == '=' || key == 'C' || key == '.' || key == 'M';
}

// Event handling
void Keypad::set_key_callback(std::function<void(char)> callback) {
    key_callback = callback;
}

void Keypad::handle_key_event() {
    char key = get_pressed_key();
    if (key != '\0' && is_valid_key(key)) {
        if (key_callback) {
            key_callback(key);
        }
        debounce_delay();
    }
}

// Status checking
bool Keypad::is_initialized() const {
    return initialized;
}

uint32_t Keypad::get_last_key_time() const {
    return last_key_time;
}

// GPIO control
void Keypad::set_row_pins(GPIO_TypeDef* port, uint16_t* pins) {
    row_port = port;
    memcpy(row_pins, pins, sizeof(row_pins));
}

void Keypad::set_col_pins(GPIO_TypeDef* port, uint16_t* pins) {
    col_port = port;
    memcpy(col_pins, pins, sizeof(col_pins));
}

// Private helper methods
void Keypad::scan_matrix() {
    // This method is called internally by scan_key()
}

char Keypad::decode_key(uint8_t row, uint8_t col) {
    // Keypad layout:
    // Row 0: 1, 2, 3, A
    // Row 1: 4, 5, 6, B
    // Row 2: 7, 8, 9, C
    // Row 3: *, 0, #, D
    
    static const char keymap[4][4] = {
        {'1', '2', '3', '+'},
        {'4', '5', '6', '-'},
        {'7', '8', '9', '*'},
        {'C', '0', '=', '/'}
    };
    
    if (row < 4 && col < 4) {
        return keymap[row][col];
    }
    
    return '\0';
}

bool Keypad::read_row(uint8_t row) {
    if (row_port == nullptr || row >= 4) {
        return false;
    }
    
    return HAL_GPIO_ReadPin(row_port, row_pins[row]) == GPIO_PIN_SET;
}

bool Keypad::read_column(uint8_t col) {
    if (col_port == nullptr || col >= 4) {
        return false;
    }
    
    return HAL_GPIO_ReadPin(col_port, col_pins[col]) == GPIO_PIN_RESET;
}

void Keypad::set_row_high(uint8_t row) {
    if (row_port != nullptr && row < 4) {
        HAL_GPIO_WritePin(row_port, row_pins[row], GPIO_PIN_SET);
    }
}

void Keypad::set_row_low(uint8_t row) {
    if (row_port != nullptr && row < 4) {
        HAL_GPIO_WritePin(row_port, row_pins[row], GPIO_PIN_RESET);
    }
}

void Keypad::set_col_high(uint8_t col) {
    if (col_port != nullptr && col < 4) {
        HAL_GPIO_WritePin(col_port, col_pins[col], GPIO_PIN_SET);
    }
}

void Keypad::set_col_low(uint8_t col) {
    if (col_port != nullptr && col < 4) {
        HAL_GPIO_WritePin(col_port, col_pins[col], GPIO_PIN_RESET);
    }
}

// Timer handling
void Keypad::start_timer() {
    // This would need to be implemented based on your timer configuration
}

void Keypad::stop_timer() {
    // This would need to be implemented based on your timer configuration
}

void Keypad::timer_callback() {
    // This would need to be implemented based on your timer configuration
}
