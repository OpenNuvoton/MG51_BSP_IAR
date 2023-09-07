/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"

BIT int1flag;

/************************************************************************************************************/
/* FUNCTION_PURPOSE: External INT1 interrupt Service Routine                                                          */
/************************************************************************************************************/
#pragma vector=0x13
__interrupt void INT1_ISR(void){
    PUSH_SFRS;
  
    clr_TCON_IE1;          //clr int flag wait next falling edge
    int1flag =1;
    
    POP_SFRS;
}

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void) 
{
    /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r Test start ... \n\r");
  
    P17_QUASI_MODE;                      //setting INT0 pin P1.7 as Quasi mode with internal pull high  
    P17 = 1;
    INT1_LOW_LEVEL_TRIG;                //setting trig condition level or edge
    ENABLE_INT1_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;            //Global interrupt enable
    while(1)
    {
       if (int1flag)
       {
         printf("\n\r INT1 interrupt ! \n\r");
         int1flag = 0;
       }
    }
      
}



