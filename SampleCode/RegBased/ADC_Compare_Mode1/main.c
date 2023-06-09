/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "MG51_IAR.H"

void main (void)
{
    /* Initial UART0 for pVrintf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf_UART ("\n ADC compare mode for MG51 test start... ");

    ENABLE_ADC_AIN4;
    clr_ADCCON0_ADCF;
    /* ADC Sampling time setting*/
    ADC_ConvertTime(ADC_ADCDIV2,ADC_ADCAQT5);
  
    /*Enable ADC comapre value*/
    ADC_ComapreMode(ENABLE,0x03FF);
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS; // ADC start trig signal

    while(1)
    {
        if (ADCF)
        {
          printf_UART ("\n MG51 ADC compare value same as setting");
          clr_ADCCON0_ADCF;
          set_ADCCON0_ADCS;
        }
        else
        {
           if (ADCCON2&SET_BIT4)
           {
              printf_UART ("\n ADC value greater than comapre setting"); 
           }
           else if (!(ADCCON2&SET_BIT4))
           {
              printf_UART ("\n ADC value less than comapre setting"); 
           }
        }
	Timer0_Delay(24000000,500,1000);
    }

}




