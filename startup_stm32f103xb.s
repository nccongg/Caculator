/**
  ******************************************************************************
  * @file      startup_stm32f103xb.s
  * @brief     STM32F103xB devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to __main in the C library (which eventually
  *                  calls main()).
  *            After Reset the CortexM3 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m3
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack    /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the clock system initialization function.*/
  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever

.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size  Default_Handler, .-Default_Handler

/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  
  /* External Interrupts */
  .word     WWDG_IRQHandler                   /* Window WatchDog              */
  .word     PVD_IRQHandler                    /* PVD through EXTI Line detection */
  .word     TAMPER_IRQHandler                 /* Tamper and Time Stamps      */
  .word     RTC_IRQHandler                    /* RTC through the EXTI line   */
  .word     FLASH_IRQHandler                  /* FLASH                       */
  .word     RCC_IRQHandler                    /* RCC                         */
  .word     EXTI0_IRQHandler                  /* EXTI Line0                  */
  .word     EXTI1_IRQHandler                  /* EXTI Line1                  */
  .word     EXTI2_IRQHandler                  /* EXTI Line2                  */
  .word     EXTI3_IRQHandler                  /* EXTI Line3                  */
  .word     EXTI4_IRQHandler                  /* EXTI Line4                  */
  .word     DMA1_Channel1_IRQHandler          /* DMA1 Channel 1              */
  .word     DMA1_Channel2_IRQHandler          /* DMA1 Channel 2              */
  .word     DMA1_Channel3_IRQHandler          /* DMA1 Channel 3              */
  .word     DMA1_Channel4_IRQHandler          /* DMA1 Channel 4              */
  .word     DMA1_Channel5_IRQHandler          /* DMA1 Channel 5              */
  .word     DMA1_Channel6_IRQHandler          /* DMA1 Channel 6              */
  .word     DMA1_Channel7_IRQHandler          /* DMA1 Channel 7              */
  .word     ADC1_2_IRQHandler                 /* ADC1 and ADC2               */
  .word     USB_HP_CAN1_TX_IRQHandler        /* USB High Priority or CAN1 TX */
  .word     USB_LP_CAN1_RX0_IRQHandler       /* USB Low Priority or CAN1 RX0 */
  .word     CAN1_RX1_IRQHandler               /* CAN1 RX1                    */
  .word     CAN1_SCE_IRQHandler               /* CAN1 SCE                    */
  .word     EXTI9_5_IRQHandler                /* External Line[9:5]s         */
  .word     TIM1_BRK_IRQHandler              /* TIM1 Break                  */
  .word     TIM1_UP_IRQHandler               /* TIM1 Update                  */
  .word     TIM1_TRG_COM_IRQHandler          /* TIM1 Trigger and Commutation */
  .word     TIM1_CC_IRQHandler               /* TIM1 Capture Compare        */
  .word     TIM2_IRQHandler                  /* TIM2                        */
  .word     TIM3_IRQHandler                  /* TIM3                        */
  .word     TIM4_IRQHandler                  /* TIM4                        */
  .word     I2C1_EV_IRQHandler               /* I2C1 Event                  */
  .word     I2C1_ER_IRQHandler               /* I2C1 Error                  */
  .word     I2C2_EV_IRQHandler               /* I2C2 Event                  */
  .word     I2C2_ER_IRQHandler               /* I2C2 Error                  */
  .word     SPI1_IRQHandler                  /* SPI1                        */
  .word     SPI2_IRQHandler                  /* SPI2                        */
  .word     USART1_IRQHandler                /* USART1                      */
  .word     USART2_IRQHandler                /* USART2                      */
  .word     USART3_IRQHandler                /* USART3                      */
  .word     EXTI15_10_IRQHandler             /* External Line[15:10]s       */
  .word     RTCAlarm_IRQHandler              /* RTC Alarm through EXTI Line */
  .word     USBWakeUp_IRQHandler             /* USB Wakeup from suspend     */
  .word     0                                /* Reserved                     */
  .word     0                                /* Reserved                     */
  .word     0                                /* Reserved                     */
  .word     0                                /* Reserved                     */
  .word     0                                /* Reserved                     */
  .word     0                                /* Reserved                     */
  .word     0                                /* Reserved                     */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak      NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak      MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler

  .weak      BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak      UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak      DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      WWDG_IRQHandler
  .thumb_set WWDG_IRQHandler,Default_Handler

  .weak      PVD_IRQHandler
  .thumb_set PVD_IRQHandler,Default_Handler

  .weak      TAMPER_IRQHandler
  .thumb_set TAMPER_IRQHandler,Default_Handler

  .weak      RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Default_Handler

  .weak      FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,Default_Handler

  .weak      RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Default_Handler

  .weak      EXTI0_IRQHandler
  .thumb_set EXTI0_IRQHandler,Default_Handler

  .weak      EXTI1_IRQHandler
  .thumb_set EXTI1_IRQHandler,Default_Handler

  .weak      EXTI2_IRQHandler
  .thumb_set EXTI2_IRQHandler,Default_Handler

  .weak      EXTI3_IRQHandler
  .thumb_set EXTI3_IRQHandler,Default_Handler

  .weak      EXTI4_IRQHandler
  .thumb_set EXTI4_IRQHandler,Default_Handler

  .weak      DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler,Default_Handler

  .weak      DMA1_Channel2_IRQHandler
  .thumb_set DMA1_Channel2_IRQHandler,Default_Handler

  .weak      DMA1_Channel3_IRQHandler
  .thumb_set DMA1_Channel3_IRQHandler,Default_Handler

  .weak      DMA1_Channel4_IRQHandler
  .thumb_set DMA1_Channel4_IRQHandler,Default_Handler

  .weak      DMA1_Channel5_IRQHandler
  .thumb_set DMA1_Channel5_IRQHandler,Default_Handler

  .weak      DMA1_Channel6_IRQHandler
  .thumb_set DMA1_Channel6_IRQHandler,Default_Handler

  .weak      DMA1_Channel7_IRQHandler
  .thumb_set DMA1_Channel7_IRQHandler,Default_Handler

  .weak      ADC1_2_IRQHandler
  .thumb_set ADC1_2_IRQHandler,Default_Handler

  .weak      USB_HP_CAN1_TX_IRQHandler
  .thumb_set USB_HP_CAN1_TX_IRQHandler,Default_Handler

  .weak      USB_LP_CAN1_RX0_IRQHandler
  .thumb_set USB_LP_CAN1_RX0_IRQHandler,Default_Handler

  .weak      CAN1_RX1_IRQHandler
  .thumb_set CAN1_RX1_IRQHandler,Default_Handler

  .weak      CAN1_SCE_IRQHandler
  .thumb_set CAN1_SCE_IRQHandler,Default_Handler

  .weak      EXTI9_5_IRQHandler
  .thumb_set EXTI9_5_IRQHandler,Default_Handler

  .weak      TIM1_BRK_IRQHandler
  .thumb_set TIM1_BRK_IRQHandler,Default_Handler

  .weak      TIM1_UP_IRQHandler
  .thumb_set TIM1_UP_IRQHandler,Default_Handler

  .weak      TIM1_TRG_COM_IRQHandler
  .thumb_set TIM1_TRG_COM_IRQHandler,Default_Handler

  .weak      TIM1_CC_IRQHandler
  .thumb_set TIM1_CC_IRQHandler,Default_Handler

  .weak      TIM2_IRQHandler
  .thumb_set TIM2_IRQHandler,Default_Handler

  .weak      TIM3_IRQHandler
  .thumb_set TIM3_IRQHandler,Default_Handler

  .weak      TIM4_IRQHandler
  .thumb_set TIM4_IRQHandler,Default_Handler

  .weak      I2C1_EV_IRQHandler
  .thumb_set I2C1_EV_IRQHandler,Default_Handler

  .weak      I2C1_ER_IRQHandler
  .thumb_set I2C1_ER_IRQHandler,Default_Handler

  .weak      I2C2_EV_IRQHandler
  .thumb_set I2C2_EV_IRQHandler,Default_Handler

  .weak      I2C2_ER_IRQHandler
  .thumb_set I2C2_ER_IRQHandler,Default_Handler

  .weak      SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak      SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler

  .weak      USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Default_Handler

  .weak      USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Default_Handler

  .weak      USART3_IRQHandler
  .thumb_set USART3_IRQHandler,Default_Handler

  .weak      EXTI15_10_IRQHandler
  .thumb_set EXTI15_10_IRQHandler,Default_Handler

  .weak      RTCAlarm_IRQHandler
  .thumb_set RTCAlarm_IRQHandler,Default_Handler

  .weak      USBWakeUp_IRQHandler
  .thumb_set USBWakeUp_IRQHandler,Default_Handler

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
