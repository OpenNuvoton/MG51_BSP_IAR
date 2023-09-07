/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MG51 BOD interrupt demo code
//***********************************************************************************************************
#include "mg51_iar.h"

unsigned char bodflag=0;

#pragma vector=0x43
__interrupt void BOD_ISR(void){
    PUSH_SFRS;
 
    clr_BODCON0_BOF;
    bodflag=1;

    POP_SFRS;
}

//----------------------------------------------------------------------------------------------//
void main (void)
{

  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r Test start ... \n\r");

    BOD_Open(Enable, VBOD_2_4, BOD_Reset_Enable);
    BOD_LowPower(LPBOD_Mode_3);
    BOD_Interrupt(Enable);
    ENABLE_GLOBAL_INTERRUPT;
    while(1)
    {

       if (bodflag)
       {
         printf("\n\r BOD interrupt! ..."); 
         bodflag = 0;
       }
  }
}



