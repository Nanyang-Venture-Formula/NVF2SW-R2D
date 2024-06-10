/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stm32f0xx_hal_can.h"

#include  <stdbool.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define A0_Pin GPIO_PIN_0
#define A0_GPIO_Port GPIOA
#define A1_Pin GPIO_PIN_1
#define A1_GPIO_Port GPIOA
#define R2D_LED_Pin GPIO_PIN_4
#define R2D_LED_GPIO_Port GPIOA
#define R2D_BTN_NO_Pin GPIO_PIN_5
#define R2D_BTN_NO_GPIO_Port GPIOA
#define R2D_SW_NC_Pin GPIO_PIN_6
#define R2D_SW_NC_GPIO_Port GPIOA
#define R2D_SW_NO_Pin GPIO_PIN_7
#define R2D_SW_NO_GPIO_Port GPIOA
#define SPI_IRQ_Pin GPIO_PIN_0
#define SPI_IRQ_GPIO_Port GPIOB
#define V_SENSE_Pin GPIO_PIN_1
#define V_SENSE_GPIO_Port GPIOB
#define USR_KEY_Pin GPIO_PIN_2
#define USR_KEY_GPIO_Port GPIOB
#define USR_LED_Pin GPIO_PIN_10
#define USR_LED_GPIO_Port GPIOB
#define R8_Pin GPIO_PIN_11
#define R8_GPIO_Port GPIOB
#define R7_Pin GPIO_PIN_12
#define R7_GPIO_Port GPIOB
#define R6_Pin GPIO_PIN_13
#define R6_GPIO_Port GPIOB
#define R5_Pin GPIO_PIN_14
#define R5_GPIO_Port GPIOB
#define R4_Pin GPIO_PIN_15
#define R4_GPIO_Port GPIOB
#define R3_Pin GPIO_PIN_8
#define R3_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
