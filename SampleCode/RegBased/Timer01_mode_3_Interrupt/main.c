/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"


/* if default 16MHz                                                     */
/* if define TIMER0_FSYS_DIV12, Timer0 = (256-56)*12/16MHz = 150us ,    */
/*                                Timer1 = (256-200)*12/16MHz = 42us ,  */
/* if define TIMER0_FSYS, Timer = (256-56)/16MHz = 12.5us               */
/*                          Timer = (256-200)/16MHz = 3.5us             */

/* if modify to 24MHz                                                   */
/* if define TIMER0_FSYS_DIV12, Timer0 = (256-56)*12/24MHz = 100us ,    */
/*                                Timer1 = (256-200)*12/24MHz = 28us ,  */


#define TH0_INIT        56
#define TL0_INIT        200

/************************************************************************************************************
*    TIMER 0 interrupt subroutine
************************************************************************************************************/
#pragma vector=0x0B
__interrupt void Timer0_ISR(void){

    PUSH_SFRS;
                
    TL0 = TL0_INIT;                              
    TF0=0;

    POP_SFRS;
}	

#pragma vector=0x1B
__interrupt void Timer1_ISR(void){
  
    PUSH_SFRS;
                
    TH0 = TH0_INIT;
    TF1=0;

    POP_SFRS;
}	

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    
    ENABLE_TIMER0_MODE3;
    TIMER0_FSYS_DIV12;
  
    P05_PUSHPULL_MODE;
    P00_PUSHPULL_MODE;
    set_P2S_T0OE;        /*output at T0 */
    set_P2S_T1OE;        /*Output at T1 */
    
    TH0 = TH0_INIT;                             /*initial counter values  */
    TL0 = TL0_INIT;    
 
    ENABLE_TIMER0_INTERRUPT;                                  /* enable Timer0 interrupt */
    ENABLE_TIMER1_INTERRUPT;                                  /* Enable Timer1 interrupt for T1 output*/
    ENABLE_GLOBAL_INTERRUPT;                    /*enable interrupts*/
    set_TCON_TR0;                               /*Timer0 run */
    set_TCON_TR1;

    while(1);
}

