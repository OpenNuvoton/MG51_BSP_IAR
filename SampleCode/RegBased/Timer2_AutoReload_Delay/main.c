/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"


BIT  timer2IntFlag;
/************************************************************************************************************
*    Timer2 interrupt subroutine
************************************************************************************************************/
#pragma vector=0x2B
__interrupt void Timer2_ISR(void){
  
    PUSH_SFRS;
  
     clr_T2CON_TF2;                                //Clear Timer2 Interrupt Flag
     timer2IntFlag =1;
     GPIO_LED ^= 1;

    POP_SFRS;
}	

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r Test Start ... \n\r");
    GPIO_LED_QUASI_MODE;

    TIMER2_DIV_512;
    TIMER2_Auto_Reload_Delay_Mode;

    RCMP2H = 0x60;            /* setting reload value */
    RCMP2L = 0xFF;

    TL2 = 0x60;
    TH2 =0xFF;

    ENABLE_TIMER2_INTERRUPT;                          // Enable Timer2 interrupt
    ENABLE_GLOBAL_INTERRUPT;
    set_T2CON_TR2;                                    // Timer2 run

    while(1)
    {
       if (timer2IntFlag)
       {
         timer2IntFlag=0;
         printf("\n\r Timer2 interrupt! \n\r");
       }
    }
}