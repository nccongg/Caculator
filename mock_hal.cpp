/**
  ******************************************************************************
  * @file    mock_hal.cpp
  * @brief   Mock implementation of STM32 HAL functions for desktop testing
  * @note    This is for testing only, not for actual STM32 deployment
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"
#include <iostream>

// Mock GPIO ports
GPIO_TypeDef* GPIOA = nullptr;
GPIO_TypeDef* GPIOB = nullptr;
GPIO_TypeDef* GPIOC = nullptr;
GPIO_TypeDef* GPIOD = nullptr;

// Mock GPIO functions
HAL_StatusTypeDef HAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct) {
    // Mock implementation - just return success
    return HAL_OK;
}

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    // Mock implementation - return random state for testing
    static int counter = 0;
    counter++;
    return (counter % 2 == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}

void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
    // Mock implementation - just print the action
    std::cout << "GPIO Write: Pin " << GPIO_Pin << " = " << (PinState == GPIO_PIN_SET ? "SET" : "RESET") << std::endl;
}

void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    // Mock implementation - just print the action
    std::cout << "GPIO Toggle: Pin " << GPIO_Pin << std::endl;
}

// Mock UART functions
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef* huart) {
    // Mock implementation - just return success
    return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef* huart, uint8_t* pData, uint16_t Size, uint32_t Timeout) {
    // Mock implementation - print the data to console
    std::cout << "UART TX [" << Size << " bytes]: ";
    for (uint16_t i = 0; i < Size; i++) {
        std::cout << (char)pData[i];
    }
    std::cout << std::endl;
    return HAL_OK;
}

// Mock Timer functions
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef* htim) {
    // Mock implementation - just return success
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef* htim) {
    // Mock implementation - just return success
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef* htim) {
    // Mock implementation - just return success
    return HAL_OK;
}

// Mock RCC functions
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef* RCC_OscInitStruct) {
    // Mock implementation - just return success
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef* RCC_ClkInitStruct, uint32_t FLatency) {
    // Mock implementation - just return success
    return HAL_OK;
}

// Mock PWR functions
HAL_StatusTypeDef HAL_PWREx_ConfigVoltageScaling(uint32_t VoltageScaling) {
    // Mock implementation - just return success
    return HAL_OK;
}
