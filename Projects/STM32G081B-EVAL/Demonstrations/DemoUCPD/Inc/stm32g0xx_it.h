/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
   * @attention
  *
  * Copyright (c) 2018 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32G0xx_IT_H
#define __STM32G0xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#if defined(_TRACE)
#include "tracer_emb_conf.h"
#endif/*_TRACE */
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
void NMI_Handler( void );
void HardFault_Handler( void );
void SysTick_Handler( void );
void UCPD1_2_IRQHandler( void );
#if defined(_TRACE)
void TRACER_EMB_USART_IRQHANDLER( void );
void TRACER_EMB_TX_DMA_IRQHANDLER( void );
#endif/*_TRACE */
void ADC1_COMP_IRQHandler( void );
void DMA1_Channel1_IRQHandler( void );
/* USER CODE BEGIN EFP */
void EXTI4_15_IRQHandler( void );
void EXTI0_1_IRQHandler( void );
void EXTI2_3_IRQHandler( void );

void DEBOUNCE_TIM_IRQHandler( void );
/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __STM32G0xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
