/**
  ******************************************************************************
  * @file    Examples_LL/COMP/COMP_CompareGpioVsVrefInt_IT/Src/stm32g0xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_it.h"

/** @addtogroup STM32G0xx_LL_Examples
  * @{
  */

/** @addtogroup COMP_CompareGpioVsVrefInt_IT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0+ Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler( void )
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler( void )
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while( 1 )
    {
    }
}


/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler( void )
{
}


/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler( void )
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler( void )
{
}

/******************************************************************************/
/*                 STM32G0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32g0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles COMP1 interrupt request.
  * @param  None
  * @retval None
  */
void ADC1_COMP_IRQHandler( void )
{
    /* Check whether EXTI line 17 (from COMP1 output) caused the interruption */
    if( LL_EXTI_IsActiveRisingFlag_0_31( LL_EXTI_LINE_17 ) != RESET )
    {
        /* Clear flag of EXTI */
        LL_EXTI_ClearRisingFlag_0_31( LL_EXTI_LINE_17 );

        /* Call interruption treatment function */
        ComparatorTrigger_Callback();
    }

    /* Check whether EXTI line 17 (from COMP1 output) caused the interruption */
    if( LL_EXTI_IsActiveFallingFlag_0_31( LL_EXTI_LINE_17 ) != RESET )
    {
        /* Clear flag of EXTI */
        LL_EXTI_ClearFallingFlag_0_31( LL_EXTI_LINE_17 );

        /* Call interruption treatment function */
        ComparatorTrigger_Callback();
    }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
