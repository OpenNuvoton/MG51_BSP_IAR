/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"


BIT captureflag;
uint8_t  capLowByte,capHighByte;
/************************************************************************************************************/
/*    Capture interrupt subroutine                                                                   */
/************************************************************************************************************/
#pragma vector=0x63
__interrupt void Capture_ISR(void){
  
    PUSH_SFRS;

    clr_CAPCON0_CAPF2;                  /* clear capture2 interrupt flag  */
    capLowByte = C2L;                   /* For capture mode CxL/CxH with data capture from I/O pin*/
    capHighByte = C2H;                    
    clr_T2CON_TF2;
    captureflag = 1;

    POP_SFRS;
}
/************************************************************************************************************/
/*    Main function                                                                                         */
/************************************************************************************************************/
void main (void)
{
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r Test start ... \n\r");
    
    P04_QUASI_MODE;
    P04 = 0;
    
    TIMER2_Compare_Capture_Mode;
    TIMER2_CAP2_Capture_Mode;
    IC3_P04_CAP2_RISINGEDGE_CAPTURE;

    ENABLE_CAPTURE_INTERRUPT;            //Enable Capture interrupt
    set_T2CON_TR2;                       //Triger Timer2
    ENABLE_GLOBAL_INTERRUPT;

    while(1)
    {
      if (captureflag)
      {
        printf("\n\r Capture low byte value = 0x%X",capLowByte);
        captureflag = 0;
      }
    }
        
}
