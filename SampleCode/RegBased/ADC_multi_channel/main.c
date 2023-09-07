/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"

uint16_t ADCdataAIN5,ADCdataVBG;

/*****************************************************************************/
/*The main C function.  Program execution starts                             */
/*here after stack initialization.                                           */
/*****************************************************************************/
void main (void) 
{
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r Test start ... \n\r");
    while(1)
    {
/*Enable channel 5 */ 
      ENABLE_ADC_AIN5;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                                
      while(ADCF == 0);
      ADCdataAIN5 = ADCRH<<4;
      ADCdataAIN5|= ADCRL&0x0F;
      DISABLE_ADC;
      
      printf("\n\r  ADC channel 5 =0x%X", ADCdataAIN5);
      Timer0_Delay(24000000,500,1000);
/*Enable Bandgap */     
      ENABLE_ADC_BANDGAP;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;
      while(ADCF == 0);
      ADCdataVBG = ADCRH<<4;
      ADCdataVBG|= ADCRL&0x0F;
      DISABLE_ADC;

      printf("\n\r  ADC channel bandgap =0x%X", ADCdataVBG);
      Timer0_Delay(16000000,500,1000);
    }  
}