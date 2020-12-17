/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CRC/CRC_PolynomialUpdate/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use the STM32G0xx CRC HAL API
  *          to compute a CRC code of a given buffer of data words (32-bit),
  *          based on a user-defined generating polynomial.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stm32g0xx_ll_crc.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define BUFFER_SIZE    2


/* The user defined polynomial*/
#define CRC_POLYNOMIAL_8B  0x9B   /* X^8 + X^7 + X^4 + X^3 + X + 1 */
#define CRC_POLYNOMIAL_16B 0x1021 /* X^16 + X^12 + X^5 + 1 */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

/* USER CODE BEGIN PV */

/* Used for storing CRC Value */
__IO uint32_t uwCRCValue = 0;

/* Buffer containing the data on which the CRC will be calculated */
static const uint32_t aDataBuffer[BUFFER_SIZE] =
{
    0x12345678, 0x12213883
};

/* Expected CRC Value */
uint32_t uwExpectedCRCValue1 = 0xAB;
uint32_t uwExpectedCRCValue2 = 0x9357;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config( void );
static void MX_CRC_Init( void );
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main( void )
{
    /* USER CODE BEGIN 1 */

    /* STM32G0xx HAL library initialization:
         - Configure the Flash prefetch
         - Systick timer is configured by default as source of time base, but user
           can eventually implement his proper time base source (a general purpose
           timer for example or other time source), keeping in mind that Time base
           duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
           handled in milliseconds basis.
         - Low Level Initialization
       */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */


    /* Configure LED4 */
    BSP_LED_Init( LED4 );

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_CRC_Init();
    /* USER CODE BEGIN 2 */

    /*##-1- Configure the CRC peripheral #######################################*/
    hcrc.Instance = CRC;

    /* The default polynomial is not used. It is required to defined it in hcrc.Init.GeneratingPolynomial*/
    hcrc.Init.DefaultPolynomialUse    = DEFAULT_POLYNOMIAL_DISABLE;

    /* Set the value of the polynomial */
    hcrc.Init.GeneratingPolynomial    = CRC_POLYNOMIAL_8B;

    /* The user-defined generating polynomial generates a
       8-bit long CRC */
    hcrc.Init.CRCLength               = CRC_POLYLENGTH_8B;

    /* The default init value is used */
    hcrc.Init.DefaultInitValueUse     = DEFAULT_INIT_VALUE_ENABLE;

    /* The input data are not inverted */
    hcrc.Init.InputDataInversionMode  = CRC_INPUTDATA_INVERSION_NONE;

    /* The output data are not inverted */
    hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;

    /* The input data are 32- bit long */
    hcrc.InputDataFormat              = CRC_INPUTDATA_FORMAT_WORDS;

    if( HAL_CRC_Init( &hcrc ) != HAL_OK )
    {
        /* Initialization Error */
        Error_Handler();
    }

    /*##-2- Compute the CRC of "aDataBuffer" ###################################*/
    /* First computation is done using 8-bit generating Polynomial (CRC_POLYNOMIAL_8B)
       as configured in CRC handle, with HAL_CRC_Init */
    uwCRCValue = HAL_CRC_Calculate( &hcrc, ( uint32_t * )&aDataBuffer, BUFFER_SIZE );

    /*##-3- Compare the CRC value to the Expected one ##########################*/
    if( uwCRCValue != uwExpectedCRCValue1 )
    {
        /* Wrong CRC value: enter Error_Handler */
        Error_Handler();
    }
    else
    {
        /* Update CRC generating polynomial length and value using LL services.
           In this case, using LL services allows to avoid calling HAL_CRC_Init()/HAL_CRC_DeInit */
        LL_CRC_SetPolynomialSize( CRC, LL_CRC_POLYLENGTH_16B );
        LL_CRC_SetPolynomialCoef( CRC, CRC_POLYNOMIAL_16B );

        /* Following code sequence is needed in order to keep CRC handle structure
           content in line with IP configuration */
        /* Set the value of the polynomial */
//    hcrc.Init.GeneratingPolynomial    = CRC_POLYNOMIAL_16B;
        /* The user-defined generating polynomial generates a 16-bit long CRC */
//    hcrc.Init.CRCLength               = CRC_POLYLENGTH_16B;

        /*##-4- Compute the CRC of "aDataBuffer" ###################################*/
        /* Second computation is done using 16-bit generating Polynomial (CRC_POLYNOMIAL_16B)
           as configured in IP using LL APIs */
        uwCRCValue = HAL_CRC_Calculate( &hcrc, ( uint32_t * )&aDataBuffer, BUFFER_SIZE );

        /*##-5- Compare the CRC value to the Expected one ##########################*/
        if( uwCRCValue != uwExpectedCRCValue2 )
        {
            /* Wrong CRC value: enter Error_Handler */
            Error_Handler();
        }
        else
        {
            /* Right CRC value: Turn LED4 on */
            BSP_LED_On( LED4 );
        }
    }

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while( 1 )
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }

    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config( void )
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    HAL_PWREx_ControlVoltageScaling( PWR_REGULATOR_VOLTAGE_SCALE1 );
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
    RCC_OscInitStruct.PLL.PLLN = 8;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;

    if( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK )
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if( HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_2 ) != HAL_OK )
    {
        Error_Handler();
    }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init( void )
{

    /* USER CODE BEGIN CRC_Init 0 */

    /* USER CODE END CRC_Init 0 */

    /* USER CODE BEGIN CRC_Init 1 */

    /* USER CODE END CRC_Init 1 */
    hcrc.Instance = CRC;
    hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
    hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
    hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
    hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
    hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;

    if( HAL_CRC_Init( &hcrc ) != HAL_OK )
    {
        Error_Handler();
    }

    /* USER CODE BEGIN CRC_Init 2 */

    /* USER CODE END CRC_Init 2 */

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler( void )
{
    /* USER CODE BEGIN Error_Handler_Debug */
    while( 1 )
    {
        /* Error if LED4 is slowly blinking (1 sec. period) */
        BSP_LED_Toggle( LED4 );
        HAL_Delay( 1000 );
    }


    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed( uint8_t *file, uint32_t line )
{
    /* USER CODE BEGIN 6 */

    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while( 1 )
    {
    }

    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
