/**
******************************************************************************
  * @file    : USB_HOST/MSC_Standalone/USB_Host/App/file_operations.c
  * @author  : MCD Application Team
  * @brief   : Write/read file on the disk.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
*********************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "file_operations.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
FIL MyFile;
FRESULT res;
UINT bytesWritten;
uint8_t rtext[200];
uint8_t wtext[] = "USB Host Library : Mass Storage Example";

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Files operations: Read/Write and compare
* @param  None
* @retval Operation result
*/
uint8_t msc_file_operations( void )
{
    UINT bytesread = 0;
    uint8_t retvalue = 0;

    USBH_UsrLog( "INFO : FatFs Initialized\n" );

    if( f_open( &MyFile, "0:USBHost.txt", FA_CREATE_ALWAYS | FA_WRITE ) != FR_OK )
    {
        USBH_ErrLog( "Cannot Open 'USBHost.txt' file \n" );
        retvalue = 1;
    }
    else
    {
        USBH_UsrLog( "Write Text:" );
        USBH_UsrLog( "INFO : 'USBHost.txt' opened for write" );
        res = f_write( &MyFile, wtext, sizeof( wtext ), &bytesWritten );
        f_close( &MyFile );

        if( ( bytesWritten == 0 ) || ( res != FR_OK ) ) /*EOF or Error*/
        {
            USBH_ErrLog( "Cannot Write on the  'USBHost.txt' file \n" );
            retvalue = 1;
        }
        else
        {
            if( f_open( &MyFile, "0:USBHost.txt", FA_READ ) != FR_OK )
            {
                USBH_ErrLog( "Cannot Open 'USBHost.txt' file for read.\n" );
                retvalue = 1;
            }
            else
            {
                USBH_UsrLog( "INFO : Text written on the 'USBHost.txt' file\n" );

                res = f_read( &MyFile, rtext, sizeof( rtext ), &bytesread );

                if( ( bytesread == 0 ) || ( res != FR_OK ) ) /*EOF or Error*/
                {
                    USBH_ErrLog( "Cannot Read from the  'USBHost.txt' file \n" );
                    retvalue = 1;
                }
                else
                {
                    USBH_UsrLog( "Read Text:" );
                    USBH_UsrLog( ( char * )rtext );
                    USBH_UsrLog( "\n" );
                }

                f_close( &MyFile );
            }

            /* Compare read data with the expected data */
            if( ( bytesread == bytesWritten ) )
            {
                USBH_UsrLog( "INFO : FatFs data compare SUCCESS" );
            }
            else
            {
                USBH_ErrLog( "FatFs data compare ERROR" );
                USBH_ErrLog( "\n" );
                retvalue = 1;
            }
        }
    }

    return ( retvalue );
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
