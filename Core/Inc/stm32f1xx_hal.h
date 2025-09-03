/**
  ******************************************************************************
  * @file    stm32f1xx_hal.h
  * @brief   This file contains all the HAL module driver header files
  * @note    This is a MOCK version for desktop testing only
  *          Not for actual STM32 deployment
  ******************************************************************************
  */

#ifndef __STM32F1xx_HAL_H
#define __STM32F1xx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cstdint>
#include <cstring>

/* Exported types ------------------------------------------------------------*/

// Mock GPIO types
typedef struct {
    uint32_t Pin;
    uint32_t Mode;
    uint32_t Pull;
    uint32_t Speed;
} GPIO_InitTypeDef;

typedef struct {
    uint32_t Instance;
    uint32_t Init;
} GPIO_TypeDef;

// Mock UART types
typedef struct {
    uint32_t Instance;
    uint32_t Init;
} UART_HandleTypeDef;

// Mock Timer types
typedef struct {
    uint32_t Instance;
    uint32_t Init;
} TIM_HandleTypeDef;

// Mock RCC types
typedef struct {
    uint32_t OscillatorType;
    uint32_t HSEState;
    uint32_t HSEPredivValue;
    uint32_t HSIState;
    struct {
        uint32_t PLLState;
        uint32_t PLLSource;
        uint32_t PLLMUL;
    } PLL;
} RCC_OscInitTypeDef;

typedef struct {
    uint32_t ClockType;
    uint32_t SYSCLKSource;
    uint32_t AHBCLKDivider;
    uint32_t APB1CLKDivider;
    uint32_t APB2CLKDivider;
} RCC_ClkInitTypeDef;

// Mock PWR types
typedef struct {
    uint32_t RegulatorVoltageScale;
} PWR_RegulatorVoltageScaleTypeDef;

/* Exported constants --------------------------------------------------------*/

// GPIO constants
#define GPIO_PIN_0                 ((uint16_t)0x0001)
#define GPIO_PIN_1                 ((uint16_t)0x0002)
#define GPIO_PIN_2                 ((uint16_t)0x0004)
#define GPIO_PIN_3                 ((uint16_t)0x0008)
#define GPIO_PIN_4                 ((uint16_t)0x0010)
#define GPIO_PIN_5                 ((uint16_t)0x0020)
#define GPIO_PIN_6                 ((uint16_t)0x0040)
#define GPIO_PIN_7                 ((uint16_t)0x0080)
#define GPIO_PIN_8                 ((uint16_t)0x0100)
#define GPIO_PIN_9                 ((uint16_t)0x0200)
#define GPIO_PIN_10                ((uint16_t)0x0400)
#define GPIO_PIN_11                ((uint16_t)0x0800)
#define GPIO_PIN_12                ((uint16_t)0x1000)
#define GPIO_PIN_13                ((uint16_t)0x2000)
#define GPIO_PIN_14                ((uint16_t)0x4000)
#define GPIO_PIN_15                ((uint16_t)0x8000)

#define GPIO_MODE_INPUT            ((uint32_t)0x00000000)
#define GPIO_MODE_OUTPUT_PP        ((uint32_t)0x00000001)
#define GPIO_MODE_OUTPUT_OD        ((uint32_t)0x00000011)
#define GPIO_MODE_AF_PP            ((uint32_t)0x00000002)
#define GPIO_MODE_AF_OD            ((uint32_t)0x00000012)

#define GPIO_NOPULL                ((uint32_t)0x00000000)
#define GPIO_PULLUP                ((uint32_t)0x00000001)
#define GPIO_PULLDOWN              ((uint32_t)0x00000002)

#define GPIO_SPEED_FREQ_LOW        ((uint32_t)0x00000000)
#define GPIO_SPEED_FREQ_MEDIUM     ((uint32_t)0x00000001)
#define GPIO_SPEED_FREQ_HIGH       ((uint32_t)0x00000002)

// GPIO Pin State enum - must be defined before macros that use it
typedef enum {
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
} GPIO_PinState;

#define GPIO_PIN_SET               ((GPIO_PinState)0x01)
#define GPIO_PIN_RESET             ((GPIO_PinState)0x00)

// GPIO ports
extern GPIO_TypeDef* GPIOA;
extern GPIO_TypeDef* GPIOB;
extern GPIO_TypeDef* GPIOC;
extern GPIO_TypeDef* GPIOD;

// UART constants
#define UART_MODE_TX               ((uint32_t)0x00000001)
#define UART_MODE_RX               ((uint32_t)0x00000002)
#define UART_MODE_TX_RX            ((uint32_t)0x00000003)

#define UART_WORDLENGTH_8B         ((uint32_t)0x00000000)
#define UART_WORDLENGTH_9B         ((uint32_t)0x00000001)

#define UART_STOPBITS_1            ((uint32_t)0x00000000)
#define UART_STOPBITS_2            ((uint32_t)0x00000002)

#define UART_PARITY_NONE           ((uint32_t)0x00000000)
#define UART_PARITY_EVEN           ((uint32_t)0x00000002)
#define UART_PARITY_ODD            ((uint32_t)0x00000001)

#define UART_HWCONTROL_NONE        ((uint32_t)0x00000000)
#define UART_HWCONTROL_RTS         ((uint32_t)0x00000001)
#define UART_HWCONTROL_CTS         ((uint32_t)0x00000002)
#define UART_HWCONTROL_RTS_CTS     ((uint32_t)0x00000003)

#define UART_OVERSAMPLING_16       ((uint32_t)0x00000000)
#define UART_OVERSAMPLING_8        ((uint32_t)0x00000001)

// Timer constants
#define TIM_COUNTERMODE_UP         ((uint32_t)0x00000000)
#define TIM_COUNTERMODE_DOWN       ((uint32_t)0x00000001)

#define TIM_CLOCKDIVISION_DIV1     ((uint32_t)0x00000000)
#define TIM_CLOCKDIVISION_DIV2     ((uint32_t)0x00000100)
#define TIM_CLOCKDIVISION_DIV4     ((uint32_t)0x00000200)

#define TIM_AUTORELOAD_PRELOAD_DISABLE ((uint32_t)0x00000000)
#define TIM_AUTORELOAD_PRELOAD_ENABLE  ((uint32_t)0x00000001)

// RCC constants
#define RCC_OSCILLATORTYPE_NONE    ((uint32_t)0x00000000)
#define RCC_OSCILLATORTYPE_HSE     ((uint32_t)0x00000001)
#define RCC_OSCILLATORTYPE_HSI     ((uint32_t)0x00000002)
#define RCC_OSCILLATORTYPE_LSE     ((uint32_t)0x00000004)
#define RCC_OSCILLATORTYPE_LSI     ((uint32_t)0x00000008)

#define RCC_HSE_OFF                ((uint32_t)0x00000000)
#define RCC_HSE_ON                 ((uint32_t)0x00000001)
#define RCC_HSE_BYPASS             ((uint32_t)0x00000005)

#define RCC_HSI_OFF                ((uint32_t)0x00000000)
#define RCC_HSI_ON                 ((uint32_t)0x00000001)

#define RCC_PLL_NONE               ((uint32_t)0x00000000)
#define RCC_PLL_ON                 ((uint32_t)0x00000001)

#define RCC_PLLSOURCE_HSE          ((uint32_t)0x00010000)
#define RCC_PLLSOURCE_HSI_DIV2     ((uint32_t)0x00000000)

#define RCC_PLL_MUL2               ((uint32_t)0x00000000)
#define RCC_PLL_MUL3               ((uint32_t)0x00040000)
#define RCC_PLL_MUL4               ((uint32_t)0x00080000)
#define RCC_PLL_MUL5               ((uint32_t)0x000C0000)
#define RCC_PLL_MUL6               ((uint32_t)0x00100000)
#define RCC_PLL_MUL7               ((uint32_t)0x00140000)
#define RCC_PLL_MUL8               ((uint32_t)0x00180000)
#define RCC_PLL_MUL9               ((uint32_t)0x001C0000)

#define RCC_SYSCLKSOURCE_HSI       ((uint32_t)0x00000000)
#define RCC_SYSCLKSOURCE_HSE       ((uint32_t)0x00000001)
#define RCC_SYSCLKSOURCE_PLLCLK    ((uint32_t)0x00000002)

#define RCC_SYSCLK_DIV1            ((uint32_t)0x00000000)
#define RCC_SYSCLK_DIV2            ((uint32_t)0x00000080)
#define RCC_SYSCLK_DIV4            ((uint32_t)0x00000090)
#define RCC_SYSCLK_DIV8            ((uint32_t)0x000000A0)
#define RCC_SYSCLK_DIV16           ((uint32_t)0x000000B0)
#define RCC_SYSCLK_DIV64           ((uint32_t)0x000000C0)
#define RCC_SYSCLK_DIV128          ((uint32_t)0x000000D0)
#define RCC_SYSCLK_DIV256          ((uint32_t)0x000000E0)
#define RCC_SYSCLK_DIV512          ((uint32_t)0x000000F0)

#define RCC_HCLK_DIV1              ((uint32_t)0x00000000)
#define RCC_HCLK_DIV2              ((uint32_t)0x00000080)
#define RCC_HCLK_DIV4              ((uint32_t)0x00000090)
#define RCC_HCLK_DIV8              ((uint32_t)0x000000A0)
#define RCC_HCLK_DIV16             ((uint32_t)0x000000B0)

#define RCC_PCLK1_DIV1             ((uint32_t)0x00000000)
#define RCC_PCLK1_DIV2             ((uint32_t)0x00000100)
#define RCC_PCLK1_DIV4             ((uint32_t)0x00000200)
#define RCC_PCLK1_DIV8             ((uint32_t)0x00000300)
#define RCC_PCLK1_DIV16            ((uint32_t)0x00000400)

#define RCC_PCLK2_DIV1             ((uint32_t)0x00000000)
#define RCC_PCLK2_DIV2             ((uint32_t)0x00002000)
#define RCC_PCLK2_DIV4             ((uint32_t)0x00004000)
#define RCC_PCLK2_DIV8             ((uint32_t)0x00006000)
#define RCC_PCLK2_DIV16            ((uint32_t)0x00008000)

// PWR constants
#define PWR_REGULATOR_VOLTAGE_SCALE1 ((uint32_t)0x00000000)
#define PWR_REGULATOR_VOLTAGE_SCALE2 ((uint32_t)0x00000001)
#define PWR_REGULATOR_VOLTAGE_SCALE3 ((uint32_t)0x00000002)

// Flash constants
#define FLASH_LATENCY_0            ((uint32_t)0x00000000)
#define FLASH_LATENCY_1            ((uint32_t)0x00000001)
#define FLASH_LATENCY_2            ((uint32_t)0x00000002)

// HAL status
typedef enum {
    HAL_OK       = 0x00,
    HAL_ERROR    = 0x01,
    HAL_BUSY     = 0x02,
    HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

/* Exported macros -----------------------------------------------------------*/

// GPIO macros
#define __HAL_RCC_GPIOA_CLK_ENABLE()   do { } while(0)
#define __HAL_RCC_GPIOB_CLK_ENABLE()   do { } while(0)
#define __HAL_RCC_GPIOC_CLK_ENABLE()   do { } while(0)
#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { } while(0)

// HAL macros
#define HAL_Delay(ms)              do { } while(0)
#define HAL_GetTick()              ((uint32_t)0)

/* Exported functions prototypes ---------------------------------------------*/

// GPIO functions
HAL_StatusTypeDef HAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

// UART functions
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef* huart);
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef* huart, uint8_t* pData, uint16_t Size, uint32_t Timeout);

// Timer functions
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef* htim);
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef* htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef* htim);

// RCC functions
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef* RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef* RCC_ClkInitStruct, uint32_t FLatency);

// PWR functions
HAL_StatusTypeDef HAL_PWREx_ConfigVoltageScaling(uint32_t VoltageScaling);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_H */
