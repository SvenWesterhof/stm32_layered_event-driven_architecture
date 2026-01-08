#ifndef BSP_H
#define BSP_H

/**
 * @file bsp.h
 * @brief Board Support Package - Board-level initialization
 * 
 * This module handles board-level initialization including:
 * - GPIO configuration
 * - Clock setup
 * - Peripheral initialization
 * - Board-specific hardware setup
 */

#include "stm32f7xx_hal.h"
#include "pinout.h"

// BSP Initialization
void BSP_Init(void);

// Board-level functions (if needed)
void BSP_LED_Init(void);
void BSP_LED_On(void);
void BSP_LED_Off(void);
void BSP_LED_Toggle(void);

#endif // BSP_H
