/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "mg51_iar.h"

void main (void)
{
    /* Initial UART0 for pVrintf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r ADC compare mode for N76S003 test start... \n\r");
  
    ENABLE_ADC_AIN4;

    /*Enable ADC comapre value*/
    ADC_ComapreMode(ENABLE,0x3FF);
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS; // ADC start trig signal
	
	  while(1)
	  {
         while (!ADCF);
         if (ADCCON2&SET_BIT4)
         {
            printf("\n\r ADC value greater than comapre setting"); 
         }
         else if (!(ADCCON2&SET_BIT4))
         {
            printf("\n\r ADC value less than comapre setting"); 
         }
         Timer0_Delay(24000000,500,1000);
         clr_ADCCON0_ADCF;
         set_ADCCON0_ADCS;
     }
}




