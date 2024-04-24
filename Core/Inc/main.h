/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define SW_RadFan_Pin GPIO_PIN_13
#define SW_RadFan_GPIO_Port GPIOC
#define LED_R_Pin GPIO_PIN_0
#define LED_R_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_1
#define LED_G_GPIO_Port GPIOA
#define LED_B_Pin GPIO_PIN_2
#define LED_B_GPIO_Port GPIOA
#define PWM_Pump_Pin GPIO_PIN_8
#define PWM_Pump_GPIO_Port GPIOA
#define PWM_Accessory_Pin GPIO_PIN_9
#define PWM_Accessory_GPIO_Port GPIOA
#define PWM_BrakeLight_Pin GPIO_PIN_10
#define PWM_BrakeLight_GPIO_Port GPIOA
#define PWM_RadFan_Pin GPIO_PIN_11
#define PWM_RadFan_GPIO_Port GPIOA
#define SW_BattFan_Pin GPIO_PIN_12
#define SW_BattFan_GPIO_Port GPIOA
#define SW_GLV_Pin GPIO_PIN_15
#define SW_GLV_GPIO_Port GPIOA
#define SW_SHDN_Pin GPIO_PIN_4
#define SW_SHDN_GPIO_Port GPIOB
#define SW_RTD_Pin GPIO_PIN_6
#define SW_RTD_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
