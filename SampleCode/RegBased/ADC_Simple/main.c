/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MG51 ADC simple convert demo code
//***********************************************************************************************************
#include "mg51_iar.h"

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/

UINT16 ADCResult12bit;

void main (void) 
{
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r Test start ... \n\r");


    ENABLE_ADC_AIN4;            

    while(1)
    {
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                  // ADC start trig signal
      while(ADCF == 0);
      ADCResult12bit = ADCRH<<4;
      ADCResult12bit|= ADCRL&0x0F;
      DISABLE_ADC;
      printf("\n\r ADCRH = 0x%X",ADCResult12bit );
      Timer0_Delay(24000000,800,1000);
      ENABLE_ADC;
    }
}


