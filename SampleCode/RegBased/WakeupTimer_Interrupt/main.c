/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"

BIT  wktflag;

#pragma vector=0x8B
__interrupt void WKT_ISR(void){
  
    PUSH_SFRS;
  
    clr_WKCON_WKTF;
    wktflag = 1;
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
    
    WKT_AutoReload_Interrupt_Initial_S(1);
    WKT_Interrupt(Enable);
    ENABLE_GLOBAL_INTERRUPT;
    wktflag = 0;
    while(1)
    {
       if(wktflag)
      {
        SFRS=0;
        printf("\n\r WKT interrupt!");
        wktflag = 0;
      }
    }
    
}

