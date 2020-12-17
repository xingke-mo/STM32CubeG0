/**
  ******************************************************************************
  * @file    CRC/CRC_Example/Src/stm32g0xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"
#include "app_calendar.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief ADC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspInit( ADC_HandleTypeDef *hadc )
{
    GPIO_InitTypeDef          GPIO_InitStruct = {0};

    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* ADC Periph clock enable */
    __HAL_RCC_ADC_CLK_ENABLE();
    /* Enable GPIO clock ****************************************/
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*##-2- Configure peripheral GPIO ##########################################*/
    /* ADC Channel GPIO pin configuration */
    GPIO_InitStruct.Pin  = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );
}

/**
  * @brief ADC MSP De-Initialization
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspDeInit( ADC_HandleTypeDef *hadc )
{
    /* Disable the ADC Periheral clock */
    __HAL_RCC_ADC_CLK_DISABLE();

    /* Force the ADC Periheral Clock Reset */
    __HAL_RCC_ADC_FORCE_RESET();

    /* Release the ADC Periheral Clock Reset */
    __HAL_RCC_ADC_RELEASE_RESET();
}

/**
  * @brief RTC MSP Initialization
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspInit( RTC_HandleTypeDef *hrtc )
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct = {0};

    /* Configure LSE as RTC clock source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;

    if( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK )
    {
        while( 1 );
    }

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;

    if( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct ) != HAL_OK )
    {
        while( 1 );
    }

    /* Enable RTC peripheral Clocks */
    __HAL_RCC_RTC_ENABLE();

    /* Configure NVIC */
    HAL_NVIC_SetPriority( RTC_TAMP_IRQn, 0x03u, 0x00u );
    HAL_NVIC_EnableIRQ( RTC_TAMP_IRQn );
}


/**
  * @brief RTC MSP De-Initialization
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspDeInit( RTC_HandleTypeDef *hrtc )
{
    /* Disable Irq */
    HAL_NVIC_DisableIRQ( RTC_TAMP_IRQn );
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
