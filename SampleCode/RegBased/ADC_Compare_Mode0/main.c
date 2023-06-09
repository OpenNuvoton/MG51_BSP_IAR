/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "MG51_IAR.H"

void main (void)
{
    /* Initial UART0 for pVrintf */
    MODIFY_HIRC(HIRC_166);
    P06_QUASI_MODE;
    UART_Open(16600000,UART0_Timer1,115200);
    ENABLE_UART0_PRINTF;
    printf_UART ("\n ADC compare mode for N76S003 test start... ");

  
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
            printf_UART ("\n ADC value greater than comapre setting"); 
         }
         else if (!(ADCCON2&SET_BIT4))
         {
            printf_UART ("\n ADC value less than comapre setting"); 
         }
         Timer0_Delay(24000000,500,1000);
         clr_ADCCON0_ADCF;
         set_ADCCON0_ADCS;
     }
}




