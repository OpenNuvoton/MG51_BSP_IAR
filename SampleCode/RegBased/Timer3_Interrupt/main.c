/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MG51 Timer 3 with interrupt demo                                                         */
/************************************************************************************************************/
#include "mg51_iar.h"

BIT   timer3IntFlag;
/************************************************************************************************************
*    TIMER 3 interrupt subroutine
************************************************************************************************************/
#pragma vector=0x83
__interrupt void Timer3_ISR(void){

    PUSH_SFRS;

    clr_T3CON_TF3;
    timer3IntFlag=1;
    GPIO_LED ^= 1;

    POP_SFRS;
}	

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{

/* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r Test start ... \n\r");
    GPIO_LED_QUASI_MODE;


    Timer3_AutoReload_Interrupt_Initial(24,300000);     // FSYS 24M,  Timer divder 128, delay 300ms)
    ENABLE_GLOBAL_INTERRUPT;                                    //enable global interrupts
    while(1)
    {
      if (timer3IntFlag)
      { 
          printf("\n\r Timer3 Interrupt ! \n ");
          timer3IntFlag=0;
      }
    }
}

