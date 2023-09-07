/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"

/* if define TIMER0_FSYS_DIV12, timer = (256-56)*12/16MHz = 150us */
/* if define TIMER0_FSYS, timer = (256-56)/16MHz = 12.5us */
#define TH1_INIT        56 
#define TL1_INIT        56

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Timer1 interrupt Service Routine                                                          */
/************************************************************************************************************/
#pragma vector=0x1B
__interrupt void Timer1_ISR(void){
  
    PUSH_SFRS;
  
    GPIO_LED ^= 1;                                 // GPIO1 toggle when interrup

    POP_SFRS;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    
    GPIO_LED_QUASI_MODE;;
    TIMER1_MODE2_ENABLE;
    TIMER1_FSYS_DIV12;
  
    TH1 = TH1_INIT;                  //initial counter values 
    TL1 = TL1_INIT;    
   
    ENABLE_TIMER1_INTERRUPT;         //enable Timer1 interrupt
    ENABLE_GLOBAL_INTERRUPT;         //enable interrupts
  
    set_TCON_TR1;                    //Timer1 run

    while(1);
}

