/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usbpd.c
  * @author  MCD Application Team
  * @brief   This file contains the device define.
  ******************************************************************************
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

/* Includes ------------------------------------------------------------------*/
#include "usbpd.h"

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */
/* USER CODE END 1 */

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* USER CODE BEGIN 2 */
/* USER CODE END 2 */

/* USBPD init function */
void MX_USBPD_Init( void )
{

    /* Global Init of USBPD HW */
    USBPD_HW_IF_GlobalHwInit();

    /* Initialize the Device Policy Manager */
    if( USBPD_OK != USBPD_DPM_InitCore() )
    {
        while( 1 );
    }

    /* Initialise the DPM application */
    if( USBPD_OK != USBPD_DPM_UserInit() )
    {
        while( 1 );
    }

    /* USER CODE BEGIN 3 */
    /* USER CODE END 3 */

    if( USBPD_OK != USBPD_DPM_InitOS() )
    {
        while( 1 );
    }

    /* USER CODE BEGIN EnableIRQ */
    /* Enable IRQ which has been disabled by FreeRTOS services */
    __enable_irq();
    /* USER CODE END EnableIRQ */

}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
