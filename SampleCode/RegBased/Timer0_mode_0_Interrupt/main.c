/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"

/* if define TIMER0_FSYS_DIV12, timer = (0x1FFF-0x1000)*12/24MHz = 4.08ms */
/* if define TIMER0_FSYS, timer = (0x1FFF-0x0010)/24MHz = 340us */
#define TH0_INIT        0x00 
#define TL0_INIT        0x10

/************************************************************************************************************
*    TIMER 0 interrupt subroutine
************************************************************************************************************/
#pragma vector=0x0B
__interrupt void Timer0_ISR(void){
  
    PUSH_SFRS;
  
    TH0 = TH0_INIT;
    TL0 = TL0_INIT;
    TF0 = 0 ;
    GPIO_LED ^= 1;                              /* GPIO toggle when interrupt  */

    POP_SFRS;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;

    ENABLE_TIMER1_MODE0;                           /* Timer 0 mode configuration */
    TIMER0_FSYS_DIV12;

    TH0 = TH0_INIT;
    TL0 = TL0_INIT;
      
    ENABLE_TIMER0_INTERRUPT;                       /* enable Timer0 interrupt  */ 
    ENABLE_GLOBAL_INTERRUPT;                       /* enable interrupts */

    set_TCON_TR0;                                  /* Timer0 run */

    while(1);

}
