/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"


/* if define TIMER0_FSYS_DIV12, timer = (0xFFFF-0x1000)*12/24MHz = 36.58ms */
/* if define TIMER0_FSYS, timer = (0xFFFF-0x1000)/24MHz = 2.548ms */
#define TH0_INIT        0x10 
#define TL0_INIT        0x00


/************************************************************************************************************/
/* FUNCTION_PURPOSE: Timer0 interrupt Service Routine                                                          */
/************************************************************************************************************/
#pragma vector=0x0B
__interrupt void Timer0_ISR(void){
  
    PUSH_SFRS;
  
    TH0 = TH0_INIT;
    TL0 = TL0_INIT;    
    TF0 = 0;
    GPIO_LED ^= 1;                     // GPIO1 toggle when interrupt

    POP_SFRS;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
  
    ENABLE_TIMER0_MODE1;
    TIMER0_FSYS;

    TH0 = TH0_INIT;
    TL0 = TL0_INIT;
    
    ENABLE_TIMER0_INTERRUPT;                       //enable Timer0 interrupt
    ENABLE_GLOBAL_INTERRUPT;                       //enable interrupts
  
    set_TCON_TR0;                                  //Timer0 run
    while(1);
}

