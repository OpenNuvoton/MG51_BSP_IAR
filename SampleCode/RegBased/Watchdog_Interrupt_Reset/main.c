/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MG51 Watchdog timer interrupt function demo                                              */
/************************************************************************************************************/
#include "MG51_IAR.H"
 
/************************************************************************************************************
*    WDT interrupt sub-routine
************************************************************************************************************/
#pragma vector=0x53
__interrupt void WDT_ISR(void){
  
_push_(SFRS);
    CLEAR_WDT_INTERRUPT_FLAG;
  /* Config Enable WDT reset and not clear couter trig reset */
  #if 0
      WDT_COUNTER_CLEAR;                  /* Clear WDT counter */
      while(WDCON&=SET_BIT6);             /* Check for the WDT counter cleared */
  
  #endif
    P05 ^= 1;
    Timer0_Delay(24000000,500,1000);
_pop_(SFRS);
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    unsigned char ct; 
/* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
    printf ("\n\r WDT RESET must enable by CONFIG ...\n\r");
    
    P05_QUASI_MODE;
/*--------------------------------------------------------
*Warning:
*Pleaes always check CONFIG WDT disable first 
*only when WDT reset disable, WDT use as pure timer
--------------------------------------------------------*/
    WDT_TIMEOUT_1_6S;                     /* Setting WDT time out */
    WDT_RUN_IN_POWERDOWN_ENABLE;          /* WDT run in POWER DOWM mode setting if needed */
    ENABLE_WDT_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    WDT_COUNTER_RUN;                      /* WDT start to run */

    for(ct=0;ct<4;ct++)
    {
      Timer0_Delay(24000000,50,1000);
      WDT_COUNTER_CLEAR;                  /* Clear WDT counter */
      while(WDCON&=SET_BIT6);             /* Check for the WDT counter cleared */
      P05 ^= 1;
    }
      set_PCON_PD;
}
